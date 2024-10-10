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
Date                   :=10/10/24
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
Objects0=$(IntermediateDirectory)/keystrokes.c++$(ObjectSuffix) $(IntermediateDirectory)/mouse.c++$(ObjectSuffix) $(IntermediateDirectory)/symbol_code.c++$(ObjectSuffix) $(IntermediateDirectory)/main.c++$(ObjectSuffix) 



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
$(IntermediateDirectory)/keystrokes.c++$(ObjectSuffix): keystrokes.c++ $(IntermediateDirectory)/keystrokes.c++$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zoer/C++/tester3/tester3/tester3/keystrokes.c++" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keystrokes.c++$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keystrokes.c++$(DependSuffix): keystrokes.c++
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keystrokes.c++$(ObjectSuffix) -MF$(IntermediateDirectory)/keystrokes.c++$(DependSuffix) -MM keystrokes.c++

$(IntermediateDirectory)/keystrokes.c++$(PreprocessSuffix): keystrokes.c++
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keystrokes.c++$(PreprocessSuffix) keystrokes.c++

$(IntermediateDirectory)/mouse.c++$(ObjectSuffix): mouse.c++ $(IntermediateDirectory)/mouse.c++$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zoer/C++/tester3/tester3/tester3/mouse.c++" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mouse.c++$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mouse.c++$(DependSuffix): mouse.c++
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mouse.c++$(ObjectSuffix) -MF$(IntermediateDirectory)/mouse.c++$(DependSuffix) -MM mouse.c++

$(IntermediateDirectory)/mouse.c++$(PreprocessSuffix): mouse.c++
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mouse.c++$(PreprocessSuffix) mouse.c++

$(IntermediateDirectory)/symbol_code.c++$(ObjectSuffix): symbol_code.c++ $(IntermediateDirectory)/symbol_code.c++$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/zoer/C++/tester3/tester3/tester3/symbol_code.c++" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/symbol_code.c++$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/symbol_code.c++$(DependSuffix): symbol_code.c++
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/symbol_code.c++$(ObjectSuffix) -MF$(IntermediateDirectory)/symbol_code.c++$(DependSuffix) -MM symbol_code.c++

$(IntermediateDirectory)/symbol_code.c++$(PreprocessSuffix): symbol_code.c++
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/symbol_code.c++$(PreprocessSuffix) symbol_code.c++

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


