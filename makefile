CFLAGS := -Wall -Wextra

linked_list: build/linked_list
	./$<

hashtable: build/hashtable
	./$<

string_builder: build/string_builder
	./$<



build/%: %.c
	@mkdir -p build
	clang $(CFLAGS) -o $@ $<


