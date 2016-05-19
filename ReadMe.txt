"Face tracker using Raspberry" project's workspace for the course "Mechatronics".

Extension of repo: https://github.com/mc-jesus/face_detect_n_track

Install by running the following commands:
	cmake .
	make

Running DisplayImage executable:
	./DisplayImage x y

Arguments:
	x -> Number of parallel processes.
	y -> No window will be shown if defined.

Examples:	
	1) ./DisplayImage 4  	-> 4 threads with 4 video displays.
	2) ./DisplayImage 4 0	-> 4 threads without video output.