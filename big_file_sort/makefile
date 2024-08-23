all: segv

segv: main.c segv.entitlements
		clang -g main.c -o segv big_file_sort.c my_qsort.c
		codesign -s - -f --entitlements segv.entitlements segv

segv.entitlements:
		/usr/libexec/PlistBuddy -c "Add :com.apple.security.get-task-allow bool true" segv.entitlements

clean:
		rm segv
		rm segv.entitlements
		rm -rf segv.dSYM
