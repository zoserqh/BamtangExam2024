
TARGET_EXEC = exec/main

BUILD_DIR = build
SOURCE_CODE_DIR = source

SOURCE_CODE = source/cell.cpp source/maze.cpp source/main.cpp 
OBJECTS = build/cell.o build/maze.o build/main.o

INCLUDE = -I. -I/usr/local/include/opencv4
LIBS = -L/usr/local/lib \
-lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect \
-lopencv_photo -lopencv_stitching -lopencv_video -lopencv_calib3d -lopencv_features2d \
-lopencv_dnn -lopencv_flann -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc \
-lopencv_core
#CXX

$(TARGET_EXEC): $(OBJECTS) 
	$(CXX) $^ $(LIBS) -o $@

$(BUILD_DIR)/%.o : $(SOURCE_CODE_DIR)/%.cpp
	mkdir -p $(BUILD_DIR) 
	$(CXX) -c $^ $(INCLUDE) -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)
	rm $(TARGET_EXEC)