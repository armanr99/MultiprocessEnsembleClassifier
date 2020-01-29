SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
FIFOS_DIR = fifos
EXECUTABLE_FILE = EnsembleClassifier.out

CC = g++
CFLAGS = -std=c++11 -I $(INCLUDE_DIR)

.PHONY: make_build_dir make_fifos_dir all clean

all: make_build_dir make_fifos_dir EnsembleClassifier LinearClassifier Voter

make_build_dir:
	mkdir -p $(BUILD_DIR)

make_fifos_dir:
	mkdir -p $(FIFOS_DIR)

#Ensemble Classifier
ENSEMBLE_CLASSIFIER_OBJECTS = $(BUILD_DIR)/EnsembleClassifierMain.o \
							  $(BUILD_DIR)/EnsembleClassifier.o \
							  $(BUILD_DIR)/Tools.o

EnsembleClassifier: $(ENSEMBLE_CLASSIFIER_OBJECTS)
	$(CC) $(ENSEMBLE_CLASSIFIER_OBJECTS) -o EnsembleClassifier.out

EnsembleClassifierMainSensitivityList = $(SRC_DIR)/EnsembleClassifierMain.cpp \
									    $(INCLUDE_DIR)/EnsembleClassifier.hpp \
									    $(INCLUDE_DIR)/Exception.hpp \
									    $(INCLUDE_DIR)/Exceptions.hpp \
									    $(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/EnsembleClassifierMain.o: $(EnsembleClassifierMainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/EnsembleClassifierMain.cpp -o $(BUILD_DIR)/EnsembleClassifierMain.o

EnsembleClassifierSensitivityList = $(SRC_DIR)/EnsembleClassifier.cpp \
									$(INCLUDE_DIR)/EnsembleClassifier.hpp \
									$(INCLUDE_DIR)/Exceptions.hpp \
									$(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/EnsembleClassifier.o: $(EnsembleClassifierSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/EnsembleClassifier.cpp -o $(BUILD_DIR)/EnsembleClassifier.o

#Linear Classifier
LINEAR_CLASSIFIER_OBJECTS = $(BUILD_DIR)/LinearClassifierMain.o \
							$(BUILD_DIR)/LinearClassifier.o \
							$(BUILD_DIR)/Tools.o

LinearClassifier: $(LINEAR_CLASSIFIER_OBJECTS)
	$(CC) $(LINEAR_CLASSIFIER_OBJECTS) -o LinearClassifier

LinearClassifierMainSensitivityList = $(SRC_DIR)/LinearClassifierMain.cpp \
									  $(INCLUDE_DIR)/LinearClassifier.hpp \
									  $(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/LinearClassifierMain.o: $(LinearClassifierMainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/LinearClassifierMain.cpp -o $(BUILD_DIR)/LinearClassifierMain.o

LinearClassifierSensitivityList = $(SRC_DIR)/LinearClassifier.cpp \
								  $(INCLUDE_DIR)/LinearClassifier.hpp \
								  $(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/LinearClassifier.o: $(LinearClassifierSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/LinearClassifier.cpp -o $(BUILD_DIR)/LinearClassifier.o

#Voter
VOTER_OBJECTS = $(BUILD_DIR)/VoterMain.o \
				$(BUILD_DIR)/Voter.o \
				$(BUILD_DIR)/Tools.o

Voter: $(VOTER_OBJECTS)
	$(CC) $(VOTER_OBJECTS) -o Voter

VoterMainSensitivityList: $(SRC_DIR)/VoterMain.cpp \
						  $(INCLUDE_DIR)/Voter.hpp
						  $(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/VoterMain.o: $(VoterMainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/VoterMain.cpp -o $(BUILD_DIR)/VoterMain.o

VoterSensitivityList = $(SRC_DIR)/Voter.cpp \
					   $(INCLUDE_DIR)/Voter.hpp \
					   $(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/Voter.o: $(VoterSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Voter.cpp -o $(BUILD_DIR)/Voter.o


#Tools
ToolsSensitivityList = $(SRC_DIR)/Tools.cpp \
					   $(INCLUDE_DIR)/Tools.hpp

$(BUILD_DIR)/Tools.o: $(ToolsSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Tools.cpp -o $(BUILD_DIR)/Tools.o

#Others
clean:
	rm -rf $(BUILD_DIR) $(FIFOS_DIR) *.o *.out
	rm -rf Voter LinearClassifier