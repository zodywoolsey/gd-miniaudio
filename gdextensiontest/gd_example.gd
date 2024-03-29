extends Node

var miniaudio := MiniaudioServer

var started := false

var loaded_audio : MiniaudioSound = MiniaudioSound.new()
var cam_projection := Vector3()

var loaded_audio_files : Array[MiniaudioSound]

var thread := Thread.new()

@onready var sound = $sound
@onready var top = $Control/HSplitContainer/SplitContainer/SubViewportContainer/top
@onready var back = $Control/HSplitContainer/SplitContainer/SubViewportContainer2/back

func _init():
	MiniaudioServer.setup_default_node_graph()
	started = true
#	MiniaudioServer.initialize_engine()
#	MiniaudioServer.start_engine()
#	MiniaudioServer.initialize_node_graph()

func _ready():
	miniaudio.load_audio_file("C:/Users/zodie/OneDrive/Documents/0assets/sunvox/exports/chill ghost zone very long.wav", loaded_audio)
	loaded_audio_files.append(loaded_audio)
	get_window().files_dropped.connect(func(files):
		for file in files:
			if file.ends_with('.wav') or file.ends_with('.flac') or file.ends_with('.mp3'):
				var tmp = MiniaudioSound.new()
				miniaudio.load_audio_file(file, tmp)
				loaded_audio_files.append(tmp)
		)
	thread.start(push_audio_from_input_device)

func push_audio_from_input_device():
	while true:
		var buffer = miniaudio.get_input_device().get_buffer()
		miniaudio.get_remote_stream().gdma_push_buffer(buffer)

func _process(delta):
	if started:
		for file in loaded_audio_files:
			miniaudio.set_sound_position(file, cam_projection.x,cam_projection.y,cam_projection.z)
			miniaudio.set_sound_velocity(file, sound.linear_velocity.x,sound.linear_velocity.y,sound.linear_velocity.z)
		sound.position = Vector3(cam_projection.x,cam_projection.y,cam_projection.z)
