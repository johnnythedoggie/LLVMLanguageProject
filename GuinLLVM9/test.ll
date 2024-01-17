; ModuleID = 'moduleName'
source_filename = "moduleName"

@printf_format = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define void @main() {
entry:
%x = alloca { { i32, i32 }, i32 }, align 8
store { { i32, i32 }, i32 } { { i32, i32 } { i32 1, i32 2 }, i32 2 }, { { i32, i32 }, i32 }* %x, align 4
%0 = getelementptr { { i32, i32 }, i32 }, { { i32, i32 }, i32 }* %x, i32 0, i32 0
%1 = getelementptr { i32, i32 }, { i32, i32 }* %0, i32 0, i32 1
store i32 2, i32* %1, align 4
%2 = load { { i32, i32 }, i32 }, { { i32, i32 }, i32 }* %x, align 4
%3 = extractvalue { { i32, i32 }, i32 } %2, 0
%4 = extractvalue { i32, i32 } %3, 1
%5 = call {} @output(i32 %4)
ret void
}

declare i32 @printf(i8*, ...)

define {} @output(i32 %0) {
entry:
%1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %0)
ret {} zeroinitializer
}
