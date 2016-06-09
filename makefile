CC=g++

CFLAGS= -std=c++11 -c -Wall

smoother: Mnj4x4Matrix.o MnjInfiniteLine.o MnjArc.o MnjCircle.o MnjInterval.o MnjLine.o MnjDirection.o GeomUtils.o\
        MnjOperators.o MnjPlane.o MnjPoint.o MnjUtility.o MnjVector.o Segment.o MnjSmootherUtils.o MnjSmoother.o\
        MnjSmoothableArc.o MnjSmoothableSegment.o MnjSmoothableLine.o TestMnjSmoother.o MnjMainDev.o MnjBiDirectionalMerge.o

	$(CC) -ggdb -Wall Mnj4x4Matrix.o MnjInfiniteLine.o MnjArc.o MnjCircle.o MnjInterval.o MnjLine.o  MnjDirection.o GeomUtils.o\
        MnjOperators.o MnjPlane.o MnjPoint.o MnjUtility.o MnjVector.o Segment.o MnjSmootherUtils.o MnjSmoother.o\
        MnjSmoothableArc.o MnjSmoothableSegment.o MnjSmoothableLine.o TestMnjSmoother.o MnjMainDev.o MnjBiDirectionalMerge.o -o smoother

Mnj4x4Matrix.o: Mnj4x4Matrix.cpp Mnj4x4Matrix.h
	$(CC) $(CFLAGS) Mnj4x4Matrix.cpp

MnjDirection.o: MnjDirection.cpp MnjDirection.h
	$(CC) $(CFLAGS) MnjDirection.cpp

MnjVector.o: MnjVector.cpp
	$(CC) $(CFLAGS) MnjVector.cpp

MnjPoint.o: MnjPoint.cpp 
	$(CC) $(CFLAGS) MnjPoint.cpp

MnjLine.o: MnjLine.cpp MnjLine.h
	$(CC) $(CFLAGS) MnjLine.cpp

MnjArc.o: MnjArc.cpp MnjArc.h
	$(CC) $(CFLAGS) MnjArc.cpp

MnjCircle.o: MnjCircle.cpp MnjCircle.h
	$(CC) $(CFLAGS) MnjCircle.cpp

MnjOperators.o: MnjOperators.cpp 
	$(CC) $(CFLAGS) MnjOperators.cpp

MnjPlane.o: MnjPlane.cpp 
	$(CC) $(CFLAGS) MnjPlane.cpp  

MnjUtility.o: MnjUtility.cpp 
	$(CC) $(CFLAGS) MnjUtility.cpp

Segment.o: Segment.cpp
	$(CC) $(CFLAGS) Segment.cpp

MnjSmootherUtils.o: MnjSmootherUtils.cpp 
	$(CC) $(CFLAGS) MnjSmootherUtils.cpp

MnjSmoother.o: MnjSmoother.cpp
	$(CC) $(CFLAGS) MnjSmoother.cpp

MnjSmoothableArc.o: MnjSmoothableArc.cpp
	$(CC) $(CFLAGS) MnjSmoothableArc.cpp

MnjSmoothableSegment.o: MnjSmoothableSegment.cpp 
	$(CC) $(CFLAGS) MnjSmoothableSegment.cpp

MnjSmoothableLine.o: MnjSmoothableLine.cpp
	$(CC) $(CFLAGS) MnjSmoothableLine.cpp

MnjInterval.o: MnjInterval.cpp
	$(CC) $(CFLAGS) MnjInterval.cpp

TestMnjSmoother.o: TestMnjSmoother.cpp
	$(CC) $(CFLAGS) TestMnjSmoother.cpp

GeomUtils.o: GeomUtils.cpp
	$(CC) $(CFLAGS) GeomUtils.cpp

MnjMainDev.o: MnjMainDev.cpp
	$(CC) $(CFLAGS) MnjMainDev.cpp

MnjBiDirectionalMerge.o: MnjBiDirectionalMerge.cpp
	$(CC) $(CFLAGS) MnjBiDirectionalMerge.cpp

MnjInfiniteLine.o: MnjInfiniteLine.cpp MnjInfiniteLine.h MnjVector.h MnjVector.cpp
	$(CC) $(CFLAGS) MnjInfiniteLine.cpp

clean:
	rm *o tool
