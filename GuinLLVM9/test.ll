; ModuleID = 'moduleName'
source_filename = "moduleName"

define void @main() {
	entry:
	%y = alloca i1, align 1
	store i1 false, i1* %y, align 1
	store i1 true, i1* %y, align 1
	ret void
}
