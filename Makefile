all: colorize

colorize: colorize.cc imageDownload.h ratioset.h pam_assistant.h
	g++ -I /usr/include/netpbm -o colorize colorize.cc ratioset.cc pam_assistant.cc -Wall -lnetpbm

clean:
	rm -f *~

clean-all: clean
	rm -f colorize
