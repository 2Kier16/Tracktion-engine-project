/*
    ,--.                     ,--.     ,--.  ,--.
  ,-'  '-.,--.--.,--,--.,---.|  |,-.,-'  '-.`--' ,---. ,--,--,      Copyright 2018
  '-.  .-'|  .--' ,-.  | .--'|     /'-.  .-',--.| .-. ||      \   Tracktion Software
    |  |  |  |  \ '-'  \ `--.|  \  \  |  |  |  |' '-' '|  ||  |       Corporation
    `---' `--'   `--`--'`---'`--'`--' `---' `--' `---' `--''--'    www.tracktion.com

    Tracktion Engine uses a GPL/commercial licence - see LICENCE.md for details.
*/

namespace tracktion_engine
{

/**
    The Engine is the central class for all tracktion sessions.

    Create a Engine before creating any edits. Pass in subclasses of behaviours to
    customise how the engine behaves or pass nullptr to use the defaults.
    To get going quickly, just use the constructor that takes an application name,
    which uses default settings.
*/
class Engine
{
public:
    Engine (juce::String applicationName);
    Engine (juce::String applicationName, std::unique_ptr<UIBehaviour>, std::unique_ptr<EngineBehaviour>);
    Engine (std::unique_ptr<PropertyStorage>, std::unique_ptr<UIBehaviour>, std::unique_ptr<EngineBehaviour>);
    ~Engine();

    /** Returns the current version of Tracktion Engine. */
    static juce::String getVersion();

   #if TRACKTION_ENABLE_SINGLETONS
    // Do not use in new projects
    static Engine& getInstance();
   #endif
    static juce::Array<Engine*> getEngines();

    TemporaryFileManager& getTemporaryFileManager() const;
    AudioFileFormatManager& getAudioFileFormatManager() const;
    PropertyStorage& getPropertyStorage() const;
    UIBehaviour& getUIBehaviour() const;
    EngineBehaviour& getEngineBehaviour() const;
    DeviceManager& getDeviceManager() const;
    MidiProgramManager& getMidiProgramManager() const;
    ExternalControllerManager& getExternalControllerManager() const;
    RenderManager& getRenderManager() const;
    BackgroundJobManager& getBackgroundJobs() const;
    AudioFileManager& getAudioFileManager() const;
    MidiLearnState& getMidiLearnState() const;
    PluginManager& getPluginManager() const;
    EditDeleter& getEditDeleter() const;
    RecordingThumbnailManager& getRecordingThumbnailManager() const;
    WaveInputRecordingThread& getWaveInputRecordingThread() const;
    ActiveEdits& getActiveEdits() const noexcept;
    GrooveTemplateManager& getGrooveTemplateManager();
    CompFactory& getCompFactory() const;
    WarpTimeFactory& getWarpTimeFactory() const;
    ProjectManager& getProjectManager() const;

    using WeakRef = juce::WeakReference<Engine>;

private:
    void initialise();

    std::unique_ptr<ProjectManager> projectManager;
    std::unique_ptr<TemporaryFileManager> temporaryFileManager;
    std::unique_ptr<AudioFileFormatManager> audioFileFormatManager;
    std::unique_ptr<DeviceManager> deviceManager;
    std::unique_ptr<MidiProgramManager> midiProgramManager;
    std::unique_ptr<PropertyStorage> propertyStorage;
    std::unique_ptr<EngineBehaviour> engineBehaviour;
    std::unique_ptr<UIBehaviour> uiBehaviour;
    std::unique_ptr<ExternalControllerManager> externalControllerManager;
    std::unique_ptr<BackgroundJobManager> backgroundJobManager;
    std::unique_ptr<RenderManager> renderManager;
    std::unique_ptr<AudioFileManager> audioFileManager;
    std::unique_ptr<MidiLearnState> midiLearnState;
    std::unique_ptr<PluginManager> pluginManager;
    std::unique_ptr<EditDeleter> editDeleter;
    std::unique_ptr<RecordingThumbnailManager> recordingThumbnailManager;
    std::unique_ptr<WaveInputRecordingThread> waveInputRecordingThread;
    std::unique_ptr<ActiveEdits> activeEdits;
    mutable std::unique_ptr<GrooveTemplateManager> grooveTemplateManager;
    mutable std::unique_ptr<CompFactory> compFactory;
    mutable std::unique_ptr<WarpTimeFactory> warpTimeFactory;

    JUCE_DECLARE_WEAK_REFERENCEABLE (Engine)
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Engine)
};

//==============================================================================
// If you are using the default implementation of PropertyStorage, and need access to the
// underlying PropertiesFile. Warning: If you have subclassed PropertyStorage, then this
// PropertiesFile will be empty. This should only be used to pass to juce::PluginListComponent
// and will be removed in future.
juce::PropertiesFile* getApplicationSettings();

} // namespace tracktion_engine
