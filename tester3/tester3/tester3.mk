##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=tester3
ConfigurationName      :=Debug
WorkspaceConfiguration :=Debug
WorkspacePath          :=/home/zoer/C++/tester3/tester3
ProjectPath            :=/home/zoer/C++/tester3/tester3/tester3
IntermediateDirectory  :=../build-$(WorkspaceConfiguration)/tester3
OutDir                 :=$(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Zoer
Date                   :=08/10/24
CodeLitePath           :=/home/zoer/.codelite
MakeDirCommand         :=mkdir -p
LinkerName             :=/usr/bin/g++-13
SharedObjectLinkerName :=/usr/bin/g++-13 -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputDirectory        :=/home/zoer/C++/tester3/tester3/build-$(WorkspaceConfiguration)/bin
OutputFile             :=../build-$(WorkspaceConfiguration)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overridden using an environment variable
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++-13
CC       := /usr/bin/gcc-13
CXXFLAGS :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
CFLAGS   :=  -gdwarf-2 -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c++$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(IntermediateDirectory)"
	@$(MakeDirCommand) "$(OutputDirectory)"

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(IntermediateDirectory)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c++$(ObjectSuffix): main.c++ $(IntermediateDirectory)/main.c++$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zoer/C++/tester3/tester3/tester3/main.c++" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c++$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c++$(DependSuffix): main.c++
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c++$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c++$(DependSuffix) -MM main.c++

$(IntermediateDirectory)/main.c++$(PreprocessSuffix): main.c++
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c++$(PreprocessSuffix) main.c++


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


