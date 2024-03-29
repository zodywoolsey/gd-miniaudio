#ifndef GDMINIAUDIO_H
#define GDMINIAUDIO_H
#include "../miniaudio/miniaudio.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/ref.hpp>
#include "miniaudio_input_device.h"
#include "gdminiaduio_remote_stream_data_source.h"

using namespace godot;

class MiniaudioSound : public RefCounted {
    GDCLASS(MiniaudioSound, RefCounted);
    protected:
        static void _bind_methods(){
            ClassDB::bind_method(D_METHOD("set_path", "new_path"), &MiniaudioSound::set_path);
            ClassDB::bind_method(D_METHOD("get_path"), &MiniaudioSound::get_path);
	        ADD_PROPERTY(PropertyInfo(Variant::STRING, "path"), "set_path", "get_path");
        }
    public:
        MiniaudioSound(){
            sound = memnew(ma_sound);
        }
        ~MiniaudioSound(){
        }
        ma_sound *sound;
        String path;
        void set_path(String new_path){
            path = new_path;
        }
        String get_path(){
            return path;
        }
};

class MiniaudioNode : public RefCounted {
    GDCLASS(MiniaudioNode, RefCounted);
    protected:
        static void _bind_methods(){}
    public:
        MiniaudioNode(){}
        ~MiniaudioNode(){}
        
};

class GDMiniaudio : public Object {
    GDCLASS(GDMiniaudio, Object);

    private:
        bool _check_engine();

    protected:
        static void _bind_methods();

    public:
        GDMiniaudio();
        ~GDMiniaudio();
        
        ma_engine engine;
        ma_engine_config engine_config;
        ma_node_graph_config node_graph_config;
        ma_node_graph node_graph;
        
        Ref<MiniaudioInputDevice> input_device;
        MiniaudioSound *input_data_source_sound;
        
        Ref<GDMiniaudioRemoteStreamDataSource> default_remote_stream;
        
        bool engine_initialized;
        bool engine_started;
        bool node_graph_initialized;
        
        void setup_default_node_graph();
        
        void set_engine_initialized(bool is_engine_initialized);
        void set_engine_started(bool is_engine_started);
        void set_node_graph_initialized(bool is_node_graph_initialized);
        bool get_engine_initialized();
        bool get_engine_started();
        bool get_node_graph_initialized();
        
        Ref<MiniaudioInputDevice> get_input_device();
        Ref<GDMiniaudioRemoteStreamDataSource> get_remote_stream();
        
        void initialize_engine();
        void start_engine();
        
        void initialize_node_graph();
        
        void play_file(String path);
        void load_audio_file(String path, Ref<MiniaudioSound> file);
        void play_sound(Ref<MiniaudioSound>  sound);
        void set_sound_position(Ref<MiniaudioSound> sound, float posx, float posy, float posz);
        void set_sound_velocity(Ref<MiniaudioSound> sound, float velx, float vely, float velz);
        Vector3 get_sound_position(Ref<MiniaudioSound> sound);
        void read_from_data_source();
};


#endif