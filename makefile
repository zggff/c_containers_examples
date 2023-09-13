CFLAGS := -Wall -Wextra

linked_list: build/linked_list
	./$<

hashtable: build/hashtable
	./$<


build/%: %.c
	@mkdir -p build
	clang $(CFLAGS) -o $@ $<


