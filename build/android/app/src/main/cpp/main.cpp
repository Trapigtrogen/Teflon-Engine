#include <EGL/egl.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

// Engine includes
#include <OGL/OGLGraphicsSystem.h>
#include <TestApplication.h>
#include <AndroidWindow.h>
#include <core/ElapsedTimer.h>

///
/// Shared state for our app.
struct AndroidEngine
{
    struct android_app* app;

    ASensorManager* sensorManager;
    const ASensor* accelerometerSensor;
    ASensorEventQueue* sensorEventQueue;

    engine::Ref<engine::OGLGraphicsSystem> graphics;
    engine::Ref<engine::GraphicsApplication> application;
    engine::Ref<engine::Window> window;
    engine::Ref<engine::ElapsedTimer> frameTimer;


    int initDisplay();
    void drawFrame();
    void deinitDisplay();

    static int32_t onInput(struct android_app* app, AInputEvent* event);
    static void onCmd(struct android_app* app, int32_t cmd);
};


///
/// Initialize an EGL context for the current display.
int AndroidEngine::initDisplay()
{
    window = new engine::AndroidWindow(app->window);
    graphics = new engine::OGLGraphicsSystem(window);
    window->setGraphics(graphics);
    application = new engine::TestApplication(window,graphics);
    window->setApplication(application);
    frameTimer = new engine::ElapsedTimer();
    frameTimer->reset();
    return 0;
}


///
/// Just the current frame in the display.
void AndroidEngine::drawFrame()
{
    if (application == 0 )
        return;
    float deltaTime = frameTimer->getTime();
    frameTimer->reset();
    application->update(deltaTime);
    application->render(window,graphics);
}


///
/// Tear down the EGL context currently associated with the display.
void AndroidEngine::deinitDisplay()
{
    graphics = 0;
    application = 0;
    window = 0;
    frameTimer = 0;
}


///
/// Process the next input event.
int32_t AndroidEngine::onInput(struct android_app* app, AInputEvent* event)
{
    struct AndroidEngine* engine = (struct AndroidEngine*)app->userData;

    switch (AInputEvent_getType(event) ) {
        case AINPUT_EVENT_TYPE_MOTION: {
            // A pressed gesture has started, the motion contains the initial starting location.
            for (int i = 0; i < AMotionEvent_getPointerCount(event); ++i) {
                int pointerId = AMotionEvent_getPointerId(event, i);
                float x = AMotionEvent_getX(event, i);
                float y = AMotionEvent_getY(event, i);
                // TODO: send pointerId, x, y to the input system;
            }
        }
            return 1;

        case AINPUT_SOURCE_TRACKBALL: {

        }
            break;

        case AINPUT_EVENT_TYPE_KEY: {
        }
            break;
    }



    return 0;
}


///
/// Process the next main command.
void AndroidEngine::onCmd(struct android_app* app, int32_t cmd)
{
    struct AndroidEngine* engine = (struct AndroidEngine*)app->userData;
    switch (cmd)
    {
    case APP_CMD_SAVE_STATE:
        break;

    // The window is being shown, get it ready.
    case APP_CMD_INIT_WINDOW:
        if (engine->app->window != NULL)
        {
            engine->initDisplay();
            engine->drawFrame();
        }
        break;

    // The window is being hidden or closed, clean it up.
    case APP_CMD_TERM_WINDOW:
        engine->deinitDisplay();
        break;

    // When our app gains focus, we start monitoring the accelerometer.
    case APP_CMD_GAINED_FOCUS:
        if (engine->accelerometerSensor != NULL)
        {
            ASensorEventQueue_enableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
            // We'd like to get 60 events per second (in us).
            ASensorEventQueue_setEventRate(engine->sensorEventQueue, engine->accelerometerSensor, (1000L/60)*1000);
        }
        break;

    // When our app loses focus, we stop monitoring the accelerometer
    // This is to avoid consuming battery while not being used.
    case APP_CMD_LOST_FOCUS:

        if (engine->accelerometerSensor != NULL)
        {
            ASensorEventQueue_disableSensor(engine->sensorEventQueue, engine->accelerometerSensor);
        }

        engine->drawFrame();
        break;
    }
}


///
/// This is the main entry point of a native application that is using
/// android_native_app_glue.  It runs in its own thread, with its own
/// event loop for receiving input events and doing other things.
void android_main(struct android_app* state)
{
    struct AndroidEngine engine;
    // Make sure glue isn't stripped.
    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = AndroidEngine::onCmd;
    state->onInputEvent = AndroidEngine::onInput;
    engine.app = state;

    // Prepare to monitor accelerometer
    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor = ASensorManager_getDefaultSensor( engine.sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue = ASensorManager_createEventQueue( engine.sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL);

    // loop waiting for stuff to do.
    while (1)
    {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source* source;

        // Loop until all events are read, then continue to draw the next frame of animation.
        while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
        {
            // Process this event.
            if (source != NULL)
            {
                source->process(state, source);
            }

            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER)
            {
                if (engine.accelerometerSensor != NULL)
                {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue, &event, 1) > 0)
                    {
//                        LOGI("accelerometer: x=%f y=%f z=%f", event.acceleration.x, event.acceleration.y, event.acceleration.z);
                    }
                }
            }

            // Check if we are exiting.
            if (state->destroyRequested != 0)
            {
                engine.deinitDisplay();
                return;
            }
        }

        // Done with events; draw next animation frame.
        engine.drawFrame();
    }
}




