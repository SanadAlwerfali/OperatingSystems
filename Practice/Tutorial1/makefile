all: print pointer oop memory vtable
print: basic_print_tutorial.c
	gcc basic_print_tutorial.c -o basic_print_tutorial
pointer: basic_pointers_tutorial.c
	gcc basic_pointers_tutorial.c -o basic_pointers_tutorial
oop: basic_OOP_tutorial.c
	gcc basic_OOP_tutorial.c -o basic_OOP_tutorial
memory: basic_memory_tutorial.c
	gcc basic_memory_tutorial.c -o basic_memory_tutorial
vtable: basic_vtable_tutorial.cpp
	g++ -std=c++11 basic_vtable_tutorial.cpp -o basic_vtable_tutorial
help:
	@echo ""
	@echo "You can build any program by using 'make <tutorial name>'"
	@echo "You can Run any program by using './<program output name>'"
	@echo ""
	@echo "**********************************************************"
	@echo "Available tutorials:"
	@echo "  - print       : Build print program"
	@echo "  - pointer     : Build pointer program"
	@echo "  - oop         : Build oop program"
	@echo "  - memory      : Build memory program"
	@echo "  - vtable      : Build v-table program"
	@echo "**********************************************************"

clean:
	@echo ""
	@echo "Delete un-needed files"
	@echo ""
	rm basic_memory_tutorial basic_pointers_tutorial basic_OOP_tutorial basic_print_tutorial basic_vtable_tutorial

