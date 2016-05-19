#$Id$

JAVASRC    = exit255.java
MAINCLASS  = exit355
CLASSES    = ${JAVASRC:.java=.class}
JARCLASSES = ${CLASSES}
JARFILE    = exit255
SUBMITDIR  = cmps012b-wm.w14 asg1

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	- rm -vf Manifest
	chmod +x ${JARFILE}

%.class : %.java
	javac $<

test :
	${JARFILE} >255.output ; echo $$? >>255.output