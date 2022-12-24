#program name
prog =Hex

#directories
srcDir =source
incDir =include
bldDir =build
binDir =binary
resDir =res

cc =g++
incl =-I$(incDir)
lib =-lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -ldl -lXinerama -lXcursor
flag =-pthread -MP -MD

classes =$(shell find $(srcDir) -name "*.cpp")
objects =$(patsubst $(srcDir)/%, $(bldDir)/%, $(classes:.cpp=.o))
dependencies =$(patsubst $(bldDir)/%, $(bldDir)/%, $(objects:.o=.d))

all:	directories $(prog)

directories:
	@mkdir -p $(binDir)
	@mkdir -p $(bldDir)

$(prog): $(objects)
	$(cc) -o $(binDir)/$@ $^ $(lib)

$(bldDir)/%.o:	$(srcDir)/%.cpp
	$(cc) -o $@ -c $< $(flag) $(incl)

clean:
	@rm -rf $(bldDir)

purge:	clean
	@rm -rf $(binDir)

install: 
	@mkdir -p /usr/share/Hex
	@mkdir -p /usr/share/Hex/res
	@cp -r $(resDir)/* /usr/share/Hex/res/
	@cp $(binDir)/$(prog) /usr/bin/

-include $(dependencies)
