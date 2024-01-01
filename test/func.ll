; ModuleID = 'c.c'
source_filename = "c.c"
target datalayout = "e-m:o-i64:64-i128:128-n32:64-S128"
target triple = "arm64-apple-macosx11.3.0"

%struct.rbNode = type { i32, i32, [2 x %struct.rbNode*] }

@root = global %struct.rbNode* null, align 8
@.str = private unnamed_addr constant [24 x i8] c"it's here!!!!!!!!!!.10\0A\00", align 1
@.str.1 = private unnamed_addr constant [24 x i8] c"it's here!!!!!!!!!!.11\0A\00", align 1
@.str.2 = private unnamed_addr constant [26 x i8] c"Duplicates Not Allowed!!\0A\00", align 1
@.str.3 = private unnamed_addr constant [24 x i8] c"it's here!!!!!!!!!!.12\0A\00", align 1
@.str.4 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!.2\0A\00", align 1
@.str.5 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!.3\0A\00", align 1
@.str.6 = private unnamed_addr constant [22 x i8] c"it's here!!!!!!!!!!0\0A\00", align 1
@.str.7 = private unnamed_addr constant [24 x i8] c"it's here!!!!!!!!!!0.1\0A\00", align 1
@.str.8 = private unnamed_addr constant [26 x i8] c"it's here!!!!!!!!!!0.1.1\0A\00", align 1
@.str.9 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!01\0A\00", align 1
@.str.10 = private unnamed_addr constant [22 x i8] c"it's here!!!!!!!!!!1\0A\00", align 1
@.str.11 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!02\0A\00", align 1
@.str.12 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!12\0A\00", align 1
@.str.13 = private unnamed_addr constant [25 x i8] c"it's here!!!!!!!!!!13.1\0A\00", align 1
@.str.14 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!13\0A\00", align 1
@.str.15 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!14\0A\00", align 1
@.str.16 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!15\0A\00", align 1
@.str.17 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!16\0A\00", align 1
@.str.18 = private unnamed_addr constant [22 x i8] c"it's here!!!!!!!!!!2\0A\00", align 1
@.str.19 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!20\0A\00", align 1
@.str.20 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!21\0A\00", align 1
@.str.21 = private unnamed_addr constant [25 x i8] c"it's here!!!!!!!!!!21.1\0A\00", align 1
@.str.22 = private unnamed_addr constant [25 x i8] c"it's here!!!!!!!!!!22.1\0A\00", align 1
@.str.23 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!22\0A\00", align 1
@.str.24 = private unnamed_addr constant [23 x i8] c"it's here!!!!!!!!!!23\0A\00", align 1
@.str.25 = private unnamed_addr constant [22 x i8] c"it's here!!!!!!!!!!3\0A\00", align 1
@.str.26 = private unnamed_addr constant [20 x i8] c"Tree not available\0A\00", align 1
@.str.27 = private unnamed_addr constant [5 x i8] c"%d  \00", align 1
@.str.28 = private unnamed_addr constant [26 x i8] c"1. Insertion\092. Deletion\0A\00", align 1
@.str.29 = private unnamed_addr constant [20 x i8] c"3. Traverse\094. Exit\00", align 1
@.str.30 = private unnamed_addr constant [20 x i8] c"\0AEnter your choice:\00", align 1
@.str.31 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.32 = private unnamed_addr constant [29 x i8] c"Enter the element to insert:\00", align 1
@.str.33 = private unnamed_addr constant [19 x i8] c"inserting..... %d\0A\00", align 1
@.str.34 = private unnamed_addr constant [29 x i8] c"Enter the element to delete:\00", align 1
@.str.35 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.36 = private unnamed_addr constant [15 x i8] c"Not available\0A\00", align 1
@.str.37 = private unnamed_addr constant [66 x i8] c"................................................................\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.rbNode* @createNode(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.rbNode*, align 8
  store i32 %0, i32* %2, align 4
  %4 = call i8* @malloc(i64 24) #3
  %5 = bitcast i8* %4 to %struct.rbNode*
  store %struct.rbNode* %5, %struct.rbNode** %3, align 8
  %6 = load i32, i32* %2, align 4
  %7 = load %struct.rbNode*, %struct.rbNode** %3, align 8
  %8 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %7, i32 0, i32 0
  store i32 %6, i32* %8, align 8
  %9 = load %struct.rbNode*, %struct.rbNode** %3, align 8
  %10 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %9, i32 0, i32 1
  store i32 0, i32* %10, align 4
  %11 = load %struct.rbNode*, %struct.rbNode** %3, align 8
  %12 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %11, i32 0, i32 2
  %13 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %12, i64 0, i64 1
  store %struct.rbNode* null, %struct.rbNode** %13, align 8
  %14 = load %struct.rbNode*, %struct.rbNode** %3, align 8
  %15 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %14, i32 0, i32 2
  %16 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %15, i64 0, i64 0
  store %struct.rbNode* null, %struct.rbNode** %16, align 8
  %17 = load %struct.rbNode*, %struct.rbNode** %3, align 8
  ret %struct.rbNode* %17
}

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @insertion(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca [98 x %struct.rbNode*], align 8
  %4 = alloca %struct.rbNode*, align 8
  %5 = alloca %struct.rbNode*, align 8
  %6 = alloca %struct.rbNode*, align 8
  %7 = alloca %struct.rbNode*, align 8
  %8 = alloca [98 x i32], align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  store %struct.rbNode* null, %struct.rbNode** %4, align 8
  store %struct.rbNode* null, %struct.rbNode** %5, align 8
  store %struct.rbNode* null, %struct.rbNode** %6, align 8
  store %struct.rbNode* null, %struct.rbNode** %7, align 8
  store i32 0, i32* %9, align 4
  store i32 0, i32* %10, align 4
  %11 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  store %struct.rbNode* %11, %struct.rbNode** %4, align 8
  %12 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %13 = icmp eq %struct.rbNode* %12, null
  br i1 %13, label %14, label %17

14:                                               ; preds = %1
  %15 = load i32, i32* %2, align 4
  %16 = call %struct.rbNode* @createNode(i32 %15)
  store %struct.rbNode* %16, %struct.rbNode** @root, align 8
  br label %366

17:                                               ; preds = %1
  %18 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %19 = load i32, i32* %9, align 4
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %20
  store %struct.rbNode* %18, %struct.rbNode** %21, align 8
  %22 = load i32, i32* %9, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %23
  store i32 0, i32* %24, align 4
  %25 = load i32, i32* %9, align 4
  %26 = add nsw i32 %25, 1
  store i32 %26, i32* %9, align 4
  %27 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str, i64 0, i64 0))
  br label %28

28:                                               ; preds = %49, %17
  %29 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %30 = icmp ne %struct.rbNode* %29, null
  br i1 %30, label %31, label %67

31:                                               ; preds = %28
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.1, i64 0, i64 0))
  %33 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %34 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %33, i32 0, i32 0
  %35 = load i32, i32* %34, align 8
  %36 = load i32, i32* %2, align 4
  %37 = icmp eq i32 %35, %36
  br i1 %37, label %38, label %40

38:                                               ; preds = %31
  %39 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.2, i64 0, i64 0))
  br label %366

40:                                               ; preds = %31
  %41 = load i32, i32* %2, align 4
  %42 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %43 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %42, i32 0, i32 0
  %44 = load i32, i32* %43, align 8
  %45 = sub nsw i32 %41, %44
  %46 = icmp sgt i32 %45, 0
  br i1 %46, label %47, label %48

47:                                               ; preds = %40
  store i32 1, i32* %10, align 4
  br label %49

48:                                               ; preds = %40
  store i32 0, i32* %10, align 4
  br label %49

49:                                               ; preds = %48, %47
  %50 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %51 = load i32, i32* %9, align 4
  %52 = sext i32 %51 to i64
  %53 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %52
  store %struct.rbNode* %50, %struct.rbNode** %53, align 8
  %54 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %55 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %54, i32 0, i32 2
  %56 = load i32, i32* %10, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %55, i64 0, i64 %57
  %59 = load %struct.rbNode*, %struct.rbNode** %58, align 8
  store %struct.rbNode* %59, %struct.rbNode** %4, align 8
  %60 = load i32, i32* %10, align 4
  %61 = load i32, i32* %9, align 4
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %62
  store i32 %60, i32* %63, align 4
  %64 = load i32, i32* %9, align 4
  %65 = add nsw i32 %64, 1
  store i32 %65, i32* %9, align 4
  %66 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i64 0, i64 0))
  br label %28

67:                                               ; preds = %28
  %68 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i64 0, i64 0))
  %69 = load i32, i32* %2, align 4
  %70 = call %struct.rbNode* @createNode(i32 %69)
  store %struct.rbNode* %70, %struct.rbNode** %5, align 8
  %71 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.5, i64 0, i64 0))
  %72 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %73 = load i32, i32* %9, align 4
  %74 = sub nsw i32 %73, 1
  %75 = sext i32 %74 to i64
  %76 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %75
  %77 = load %struct.rbNode*, %struct.rbNode** %76, align 8
  %78 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %77, i32 0, i32 2
  %79 = load i32, i32* %10, align 4
  %80 = sext i32 %79 to i64
  %81 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %78, i64 0, i64 %80
  store %struct.rbNode* %72, %struct.rbNode** %81, align 8
  br label %82

82:                                               ; preds = %361, %67
  %83 = load i32, i32* %9, align 4
  %84 = icmp sge i32 %83, 3
  br i1 %84, label %85, label %94

85:                                               ; preds = %82
  %86 = load i32, i32* %9, align 4
  %87 = sub nsw i32 %86, 1
  %88 = sext i32 %87 to i64
  %89 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %88
  %90 = load %struct.rbNode*, %struct.rbNode** %89, align 8
  %91 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %90, i32 0, i32 1
  %92 = load i32, i32* %91, align 4
  %93 = icmp eq i32 %92, 0
  br label %94

94:                                               ; preds = %85, %82
  %95 = phi i1 [ false, %82 ], [ %93, %85 ]
  br i1 %95, label %96, label %362

96:                                               ; preds = %94
  %97 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.6, i64 0, i64 0))
  %98 = load i32, i32* %9, align 4
  %99 = sub nsw i32 %98, 2
  %100 = sext i32 %99 to i64
  %101 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %100
  %102 = load i32, i32* %101, align 4
  %103 = icmp eq i32 %102, 0
  br i1 %103, label %104, label %236

104:                                              ; preds = %96
  %105 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.7, i64 0, i64 0))
  %106 = load i32, i32* %9, align 4
  %107 = sub nsw i32 %106, 2
  %108 = sext i32 %107 to i64
  %109 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %108
  %110 = load %struct.rbNode*, %struct.rbNode** %109, align 8
  %111 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %110, i32 0, i32 2
  %112 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %111, i64 0, i64 1
  %113 = load %struct.rbNode*, %struct.rbNode** %112, align 8
  store %struct.rbNode* %113, %struct.rbNode** %7, align 8
  %114 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.8, i64 0, i64 0))
  %115 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %116 = icmp ne %struct.rbNode* %115, null
  br i1 %116, label %117, label %144

117:                                              ; preds = %104
  %118 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %119 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %118, i32 0, i32 1
  %120 = load i32, i32* %119, align 4
  %121 = icmp eq i32 %120, 0
  br i1 %121, label %122, label %144

122:                                              ; preds = %117
  %123 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.9, i64 0, i64 0))
  %124 = load i32, i32* %9, align 4
  %125 = sub nsw i32 %124, 2
  %126 = sext i32 %125 to i64
  %127 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %126
  %128 = load %struct.rbNode*, %struct.rbNode** %127, align 8
  %129 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %128, i32 0, i32 1
  store i32 0, i32* %129, align 4
  %130 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %131 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %130, i32 0, i32 1
  store i32 1, i32* %131, align 4
  %132 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %133 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %132, i32 0, i32 1
  %134 = load i32, i32* %133, align 4
  %135 = load i32, i32* %9, align 4
  %136 = sub nsw i32 %135, 1
  %137 = sext i32 %136 to i64
  %138 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %137
  %139 = load %struct.rbNode*, %struct.rbNode** %138, align 8
  %140 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %139, i32 0, i32 1
  store i32 %134, i32* %140, align 4
  %141 = load i32, i32* %9, align 4
  %142 = sub nsw i32 %141, 2
  store i32 %142, i32* %9, align 4
  %143 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.10, i64 0, i64 0))
  br label %235

144:                                              ; preds = %117, %104
  %145 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.11, i64 0, i64 0))
  %146 = load i32, i32* %9, align 4
  %147 = sub nsw i32 %146, 1
  %148 = sext i32 %147 to i64
  %149 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %148
  %150 = load i32, i32* %149, align 4
  %151 = icmp eq i32 %150, 0
  br i1 %151, label %152, label %159

152:                                              ; preds = %144
  %153 = load i32, i32* %9, align 4
  %154 = sub nsw i32 %153, 1
  %155 = sext i32 %154 to i64
  %156 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %155
  %157 = load %struct.rbNode*, %struct.rbNode** %156, align 8
  store %struct.rbNode* %157, %struct.rbNode** %7, align 8
  %158 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.12, i64 0, i64 0))
  br label %190

159:                                              ; preds = %144
  %160 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.13, i64 0, i64 0))
  %161 = load i32, i32* %9, align 4
  %162 = sub nsw i32 %161, 1
  %163 = sext i32 %162 to i64
  %164 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %163
  %165 = load %struct.rbNode*, %struct.rbNode** %164, align 8
  store %struct.rbNode* %165, %struct.rbNode** %6, align 8
  %166 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %167 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %166, i32 0, i32 2
  %168 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %167, i64 0, i64 1
  %169 = load %struct.rbNode*, %struct.rbNode** %168, align 8
  store %struct.rbNode* %169, %struct.rbNode** %7, align 8
  %170 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %171 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %170, i32 0, i32 2
  %172 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %171, i64 0, i64 0
  %173 = load %struct.rbNode*, %struct.rbNode** %172, align 8
  %174 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %175 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %174, i32 0, i32 2
  %176 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %175, i64 0, i64 1
  store %struct.rbNode* %173, %struct.rbNode** %176, align 8
  %177 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %178 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %179 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %178, i32 0, i32 2
  %180 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %179, i64 0, i64 0
  store %struct.rbNode* %177, %struct.rbNode** %180, align 8
  %181 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %182 = load i32, i32* %9, align 4
  %183 = sub nsw i32 %182, 2
  %184 = sext i32 %183 to i64
  %185 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %184
  %186 = load %struct.rbNode*, %struct.rbNode** %185, align 8
  %187 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %186, i32 0, i32 2
  %188 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %187, i64 0, i64 0
  store %struct.rbNode* %181, %struct.rbNode** %188, align 8
  %189 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.14, i64 0, i64 0))
  br label %190

190:                                              ; preds = %159, %152
  %191 = load i32, i32* %9, align 4
  %192 = sub nsw i32 %191, 2
  %193 = sext i32 %192 to i64
  %194 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %193
  %195 = load %struct.rbNode*, %struct.rbNode** %194, align 8
  store %struct.rbNode* %195, %struct.rbNode** %6, align 8
  %196 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %197 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %196, i32 0, i32 1
  store i32 0, i32* %197, align 4
  %198 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %199 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %198, i32 0, i32 1
  store i32 1, i32* %199, align 4
  %200 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %201 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %200, i32 0, i32 2
  %202 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %201, i64 0, i64 1
  %203 = load %struct.rbNode*, %struct.rbNode** %202, align 8
  %204 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %205 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %204, i32 0, i32 2
  %206 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %205, i64 0, i64 0
  store %struct.rbNode* %203, %struct.rbNode** %206, align 8
  %207 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %208 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %209 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %208, i32 0, i32 2
  %210 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %209, i64 0, i64 1
  store %struct.rbNode* %207, %struct.rbNode** %210, align 8
  %211 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.15, i64 0, i64 0))
  %212 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %213 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %214 = icmp eq %struct.rbNode* %212, %213
  br i1 %214, label %215, label %218

215:                                              ; preds = %190
  %216 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  store %struct.rbNode* %216, %struct.rbNode** @root, align 8
  %217 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.16, i64 0, i64 0))
  br label %233

218:                                              ; preds = %190
  %219 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %220 = load i32, i32* %9, align 4
  %221 = sub nsw i32 %220, 3
  %222 = sext i32 %221 to i64
  %223 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %222
  %224 = load %struct.rbNode*, %struct.rbNode** %223, align 8
  %225 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %224, i32 0, i32 2
  %226 = load i32, i32* %9, align 4
  %227 = sub nsw i32 %226, 3
  %228 = sext i32 %227 to i64
  %229 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %228
  %230 = load i32, i32* %229, align 4
  %231 = sext i32 %230 to i64
  %232 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %225, i64 0, i64 %231
  store %struct.rbNode* %219, %struct.rbNode** %232, align 8
  br label %233

233:                                              ; preds = %218, %215
  %234 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.17, i64 0, i64 0))
  br label %362

235:                                              ; preds = %122
  br label %361

236:                                              ; preds = %96
  %237 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.18, i64 0, i64 0))
  %238 = load i32, i32* %9, align 4
  %239 = sub nsw i32 %238, 2
  %240 = sext i32 %239 to i64
  %241 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %240
  %242 = load %struct.rbNode*, %struct.rbNode** %241, align 8
  %243 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %242, i32 0, i32 2
  %244 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %243, i64 0, i64 0
  %245 = load %struct.rbNode*, %struct.rbNode** %244, align 8
  store %struct.rbNode* %245, %struct.rbNode** %7, align 8
  %246 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %247 = icmp ne %struct.rbNode* %246, null
  br i1 %247, label %248, label %272

248:                                              ; preds = %236
  %249 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %250 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %249, i32 0, i32 1
  %251 = load i32, i32* %250, align 4
  %252 = icmp eq i32 %251, 0
  br i1 %252, label %253, label %272

253:                                              ; preds = %248
  %254 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.19, i64 0, i64 0))
  %255 = load i32, i32* %9, align 4
  %256 = sub nsw i32 %255, 2
  %257 = sext i32 %256 to i64
  %258 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %257
  %259 = load %struct.rbNode*, %struct.rbNode** %258, align 8
  %260 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %259, i32 0, i32 1
  store i32 0, i32* %260, align 4
  %261 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %262 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %261, i32 0, i32 1
  store i32 1, i32* %262, align 4
  %263 = load i32, i32* %9, align 4
  %264 = sub nsw i32 %263, 1
  %265 = sext i32 %264 to i64
  %266 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %265
  %267 = load %struct.rbNode*, %struct.rbNode** %266, align 8
  %268 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %267, i32 0, i32 1
  store i32 1, i32* %268, align 4
  %269 = load i32, i32* %9, align 4
  %270 = sub nsw i32 %269, 2
  store i32 %270, i32* %9, align 4
  %271 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.20, i64 0, i64 0))
  br label %360

272:                                              ; preds = %248, %236
  %273 = load i32, i32* %9, align 4
  %274 = sub nsw i32 %273, 1
  %275 = sext i32 %274 to i64
  %276 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %275
  %277 = load i32, i32* %276, align 4
  %278 = icmp eq i32 %277, 1
  br i1 %278, label %279, label %286

279:                                              ; preds = %272
  %280 = load i32, i32* %9, align 4
  %281 = sub nsw i32 %280, 1
  %282 = sext i32 %281 to i64
  %283 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %282
  %284 = load %struct.rbNode*, %struct.rbNode** %283, align 8
  store %struct.rbNode* %284, %struct.rbNode** %7, align 8
  %285 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.21, i64 0, i64 0))
  br label %317

286:                                              ; preds = %272
  %287 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.22, i64 0, i64 0))
  %288 = load i32, i32* %9, align 4
  %289 = sub nsw i32 %288, 1
  %290 = sext i32 %289 to i64
  %291 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %290
  %292 = load %struct.rbNode*, %struct.rbNode** %291, align 8
  store %struct.rbNode* %292, %struct.rbNode** %6, align 8
  %293 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %294 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %293, i32 0, i32 2
  %295 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %294, i64 0, i64 0
  %296 = load %struct.rbNode*, %struct.rbNode** %295, align 8
  store %struct.rbNode* %296, %struct.rbNode** %7, align 8
  %297 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %298 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %297, i32 0, i32 2
  %299 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %298, i64 0, i64 1
  %300 = load %struct.rbNode*, %struct.rbNode** %299, align 8
  %301 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %302 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %301, i32 0, i32 2
  %303 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %302, i64 0, i64 0
  store %struct.rbNode* %300, %struct.rbNode** %303, align 8
  %304 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %305 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %306 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %305, i32 0, i32 2
  %307 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %306, i64 0, i64 1
  store %struct.rbNode* %304, %struct.rbNode** %307, align 8
  %308 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %309 = load i32, i32* %9, align 4
  %310 = sub nsw i32 %309, 2
  %311 = sext i32 %310 to i64
  %312 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %311
  %313 = load %struct.rbNode*, %struct.rbNode** %312, align 8
  %314 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %313, i32 0, i32 2
  %315 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %314, i64 0, i64 1
  store %struct.rbNode* %308, %struct.rbNode** %315, align 8
  %316 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.23, i64 0, i64 0))
  br label %317

317:                                              ; preds = %286, %279
  %318 = load i32, i32* %9, align 4
  %319 = sub nsw i32 %318, 2
  %320 = sext i32 %319 to i64
  %321 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %320
  %322 = load %struct.rbNode*, %struct.rbNode** %321, align 8
  store %struct.rbNode* %322, %struct.rbNode** %6, align 8
  %323 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %324 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %323, i32 0, i32 1
  store i32 1, i32* %324, align 4
  %325 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %326 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %325, i32 0, i32 1
  store i32 0, i32* %326, align 4
  %327 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %328 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %327, i32 0, i32 2
  %329 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %328, i64 0, i64 0
  %330 = load %struct.rbNode*, %struct.rbNode** %329, align 8
  %331 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %332 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %331, i32 0, i32 2
  %333 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %332, i64 0, i64 1
  store %struct.rbNode* %330, %struct.rbNode** %333, align 8
  %334 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %335 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %336 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %335, i32 0, i32 2
  %337 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %336, i64 0, i64 0
  store %struct.rbNode* %334, %struct.rbNode** %337, align 8
  %338 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %339 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %340 = icmp eq %struct.rbNode* %338, %339
  br i1 %340, label %341, label %343

341:                                              ; preds = %317
  %342 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  store %struct.rbNode* %342, %struct.rbNode** @root, align 8
  br label %358

343:                                              ; preds = %317
  %344 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %345 = load i32, i32* %9, align 4
  %346 = sub nsw i32 %345, 3
  %347 = sext i32 %346 to i64
  %348 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %347
  %349 = load %struct.rbNode*, %struct.rbNode** %348, align 8
  %350 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %349, i32 0, i32 2
  %351 = load i32, i32* %9, align 4
  %352 = sub nsw i32 %351, 3
  %353 = sext i32 %352 to i64
  %354 = getelementptr inbounds [98 x i32], [98 x i32]* %8, i64 0, i64 %353
  %355 = load i32, i32* %354, align 4
  %356 = sext i32 %355 to i64
  %357 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %350, i64 0, i64 %356
  store %struct.rbNode* %344, %struct.rbNode** %357, align 8
  br label %358

358:                                              ; preds = %343, %341
  %359 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.24, i64 0, i64 0))
  br label %362

360:                                              ; preds = %253
  br label %361

361:                                              ; preds = %360, %235
  br label %82

362:                                              ; preds = %358, %233, %94
  %363 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.25, i64 0, i64 0))
  %364 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %365 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %364, i32 0, i32 1
  store i32 1, i32* %365, align 4
  br label %366

366:                                              ; preds = %362, %38, %14
  ret void
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @deletion(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca [98 x %struct.rbNode*], align 8
  %4 = alloca %struct.rbNode*, align 8
  %5 = alloca %struct.rbNode*, align 8
  %6 = alloca %struct.rbNode*, align 8
  %7 = alloca %struct.rbNode*, align 8
  %8 = alloca %struct.rbNode*, align 8
  %9 = alloca %struct.rbNode*, align 8
  %10 = alloca [98 x i32], align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  store i32 0, i32* %11, align 4
  %15 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %16 = icmp eq %struct.rbNode* %15, null
  br i1 %16, label %17, label %19

17:                                               ; preds = %1
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.26, i64 0, i64 0))
  br label %780

19:                                               ; preds = %1
  %20 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  store %struct.rbNode* %20, %struct.rbNode** %4, align 8
  br label %21

21:                                               ; preds = %41, %19
  %22 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %23 = icmp ne %struct.rbNode* %22, null
  br i1 %23, label %24, label %58

24:                                               ; preds = %21
  %25 = load i32, i32* %2, align 4
  %26 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %27 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %26, i32 0, i32 0
  %28 = load i32, i32* %27, align 8
  %29 = sub nsw i32 %25, %28
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %31, label %32

31:                                               ; preds = %24
  br label %58

32:                                               ; preds = %24
  %33 = load i32, i32* %2, align 4
  %34 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %35 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %34, i32 0, i32 0
  %36 = load i32, i32* %35, align 8
  %37 = sub nsw i32 %33, %36
  %38 = icmp sgt i32 %37, 0
  br i1 %38, label %39, label %40

39:                                               ; preds = %32
  store i32 1, i32* %12, align 4
  br label %41

40:                                               ; preds = %32
  store i32 0, i32* %12, align 4
  br label %41

41:                                               ; preds = %40, %39
  %42 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %43 = load i32, i32* %11, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %44
  store %struct.rbNode* %42, %struct.rbNode** %45, align 8
  %46 = load i32, i32* %12, align 4
  %47 = load i32, i32* %11, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %48
  store i32 %46, i32* %49, align 4
  %50 = load i32, i32* %11, align 4
  %51 = add nsw i32 %50, 1
  store i32 %51, i32* %11, align 4
  %52 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %53 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %52, i32 0, i32 2
  %54 = load i32, i32* %12, align 4
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %53, i64 0, i64 %55
  %57 = load %struct.rbNode*, %struct.rbNode** %56, align 8
  store %struct.rbNode* %57, %struct.rbNode** %4, align 8
  br label %21

58:                                               ; preds = %31, %21
  %59 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %60 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %59, i32 0, i32 2
  %61 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %60, i64 0, i64 1
  %62 = load %struct.rbNode*, %struct.rbNode** %61, align 8
  %63 = icmp eq %struct.rbNode* %62, null
  br i1 %63, label %64, label %108

64:                                               ; preds = %58
  %65 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %66 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %67 = icmp eq %struct.rbNode* %65, %66
  br i1 %67, label %68, label %77

68:                                               ; preds = %64
  %69 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %70 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %69, i32 0, i32 2
  %71 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %70, i64 0, i64 0
  %72 = load %struct.rbNode*, %struct.rbNode** %71, align 8
  %73 = icmp eq %struct.rbNode* %72, null
  br i1 %73, label %74, label %77

74:                                               ; preds = %68
  %75 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %76 = bitcast %struct.rbNode* %75 to i8*
  call void @free(i8* %76)
  store %struct.rbNode* null, %struct.rbNode** @root, align 8
  br label %107

77:                                               ; preds = %68, %64
  %78 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %79 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %80 = icmp eq %struct.rbNode* %78, %79
  br i1 %80, label %81, label %88

81:                                               ; preds = %77
  %82 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %83 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %82, i32 0, i32 2
  %84 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %83, i64 0, i64 0
  %85 = load %struct.rbNode*, %struct.rbNode** %84, align 8
  store %struct.rbNode* %85, %struct.rbNode** @root, align 8
  %86 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %87 = bitcast %struct.rbNode* %86 to i8*
  call void @free(i8* %87)
  br label %106

88:                                               ; preds = %77
  %89 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %90 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %89, i32 0, i32 2
  %91 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %90, i64 0, i64 0
  %92 = load %struct.rbNode*, %struct.rbNode** %91, align 8
  %93 = load i32, i32* %11, align 4
  %94 = sub nsw i32 %93, 1
  %95 = sext i32 %94 to i64
  %96 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %95
  %97 = load %struct.rbNode*, %struct.rbNode** %96, align 8
  %98 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %97, i32 0, i32 2
  %99 = load i32, i32* %11, align 4
  %100 = sub nsw i32 %99, 1
  %101 = sext i32 %100 to i64
  %102 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %101
  %103 = load i32, i32* %102, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %98, i64 0, i64 %104
  store %struct.rbNode* %92, %struct.rbNode** %105, align 8
  br label %106

106:                                              ; preds = %88, %81
  br label %107

107:                                              ; preds = %106, %74
  br label %258

108:                                              ; preds = %58
  %109 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %110 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %109, i32 0, i32 2
  %111 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %110, i64 0, i64 1
  %112 = load %struct.rbNode*, %struct.rbNode** %111, align 8
  store %struct.rbNode* %112, %struct.rbNode** %5, align 8
  %113 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %114 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %113, i32 0, i32 2
  %115 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %114, i64 0, i64 0
  %116 = load %struct.rbNode*, %struct.rbNode** %115, align 8
  %117 = icmp eq %struct.rbNode* %116, null
  br i1 %117, label %118, label %167

118:                                              ; preds = %108
  %119 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %120 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %119, i32 0, i32 2
  %121 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %120, i64 0, i64 0
  %122 = load %struct.rbNode*, %struct.rbNode** %121, align 8
  %123 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %124 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %123, i32 0, i32 2
  %125 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %124, i64 0, i64 0
  store %struct.rbNode* %122, %struct.rbNode** %125, align 8
  %126 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %127 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %126, i32 0, i32 1
  %128 = load i32, i32* %127, align 4
  store i32 %128, i32* %14, align 4
  %129 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %130 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %129, i32 0, i32 1
  %131 = load i32, i32* %130, align 4
  %132 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %133 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %132, i32 0, i32 1
  store i32 %131, i32* %133, align 4
  %134 = load i32, i32* %14, align 4
  %135 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %136 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %135, i32 0, i32 1
  store i32 %134, i32* %136, align 4
  %137 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %138 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %139 = icmp eq %struct.rbNode* %137, %138
  br i1 %139, label %140, label %142

140:                                              ; preds = %118
  %141 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  store %struct.rbNode* %141, %struct.rbNode** @root, align 8
  br label %157

142:                                              ; preds = %118
  %143 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %144 = load i32, i32* %11, align 4
  %145 = sub nsw i32 %144, 1
  %146 = sext i32 %145 to i64
  %147 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %146
  %148 = load %struct.rbNode*, %struct.rbNode** %147, align 8
  %149 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %148, i32 0, i32 2
  %150 = load i32, i32* %11, align 4
  %151 = sub nsw i32 %150, 1
  %152 = sext i32 %151 to i64
  %153 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %152
  %154 = load i32, i32* %153, align 4
  %155 = sext i32 %154 to i64
  %156 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %149, i64 0, i64 %155
  store %struct.rbNode* %143, %struct.rbNode** %156, align 8
  br label %157

157:                                              ; preds = %142, %140
  %158 = load i32, i32* %11, align 4
  %159 = sext i32 %158 to i64
  %160 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %159
  store i32 1, i32* %160, align 4
  %161 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %162 = load i32, i32* %11, align 4
  %163 = sext i32 %162 to i64
  %164 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %163
  store %struct.rbNode* %161, %struct.rbNode** %164, align 8
  %165 = load i32, i32* %11, align 4
  %166 = add nsw i32 %165, 1
  store i32 %166, i32* %11, align 4
  br label %257

167:                                              ; preds = %108
  %168 = load i32, i32* %11, align 4
  store i32 %168, i32* %13, align 4
  %169 = load i32, i32* %11, align 4
  %170 = add nsw i32 %169, 1
  store i32 %170, i32* %11, align 4
  br label %171

171:                                              ; preds = %167, %191
  %172 = load i32, i32* %11, align 4
  %173 = sext i32 %172 to i64
  %174 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %173
  store i32 0, i32* %174, align 4
  %175 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %176 = load i32, i32* %11, align 4
  %177 = sext i32 %176 to i64
  %178 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %177
  store %struct.rbNode* %175, %struct.rbNode** %178, align 8
  %179 = load i32, i32* %11, align 4
  %180 = add nsw i32 %179, 1
  store i32 %180, i32* %11, align 4
  %181 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %182 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %181, i32 0, i32 2
  %183 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %182, i64 0, i64 0
  %184 = load %struct.rbNode*, %struct.rbNode** %183, align 8
  store %struct.rbNode* %184, %struct.rbNode** %6, align 8
  %185 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %186 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %185, i32 0, i32 2
  %187 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %186, i64 0, i64 0
  %188 = load %struct.rbNode*, %struct.rbNode** %187, align 8
  %189 = icmp eq %struct.rbNode* %188, null
  br i1 %189, label %190, label %191

190:                                              ; preds = %171
  br label %193

191:                                              ; preds = %171
  %192 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  store %struct.rbNode* %192, %struct.rbNode** %5, align 8
  br label %171

193:                                              ; preds = %190
  %194 = load i32, i32* %13, align 4
  %195 = sext i32 %194 to i64
  %196 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %195
  store i32 1, i32* %196, align 4
  %197 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %198 = load i32, i32* %13, align 4
  %199 = sext i32 %198 to i64
  %200 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %199
  store %struct.rbNode* %197, %struct.rbNode** %200, align 8
  %201 = load i32, i32* %13, align 4
  %202 = icmp sgt i32 %201, 0
  br i1 %202, label %203, label %218

203:                                              ; preds = %193
  %204 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %205 = load i32, i32* %13, align 4
  %206 = sub nsw i32 %205, 1
  %207 = sext i32 %206 to i64
  %208 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %207
  %209 = load %struct.rbNode*, %struct.rbNode** %208, align 8
  %210 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %209, i32 0, i32 2
  %211 = load i32, i32* %13, align 4
  %212 = sub nsw i32 %211, 1
  %213 = sext i32 %212 to i64
  %214 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %213
  %215 = load i32, i32* %214, align 4
  %216 = sext i32 %215 to i64
  %217 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %210, i64 0, i64 %216
  store %struct.rbNode* %204, %struct.rbNode** %217, align 8
  br label %218

218:                                              ; preds = %203, %193
  %219 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %220 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %219, i32 0, i32 2
  %221 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %220, i64 0, i64 0
  %222 = load %struct.rbNode*, %struct.rbNode** %221, align 8
  %223 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %224 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %223, i32 0, i32 2
  %225 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %224, i64 0, i64 0
  store %struct.rbNode* %222, %struct.rbNode** %225, align 8
  %226 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %227 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %226, i32 0, i32 2
  %228 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %227, i64 0, i64 1
  %229 = load %struct.rbNode*, %struct.rbNode** %228, align 8
  %230 = load %struct.rbNode*, %struct.rbNode** %5, align 8
  %231 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %230, i32 0, i32 2
  %232 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %231, i64 0, i64 0
  store %struct.rbNode* %229, %struct.rbNode** %232, align 8
  %233 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %234 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %233, i32 0, i32 2
  %235 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %234, i64 0, i64 1
  %236 = load %struct.rbNode*, %struct.rbNode** %235, align 8
  %237 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %238 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %237, i32 0, i32 2
  %239 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %238, i64 0, i64 1
  store %struct.rbNode* %236, %struct.rbNode** %239, align 8
  %240 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %241 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %242 = icmp eq %struct.rbNode* %240, %241
  br i1 %242, label %243, label %245

243:                                              ; preds = %218
  %244 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  store %struct.rbNode* %244, %struct.rbNode** @root, align 8
  br label %245

245:                                              ; preds = %243, %218
  %246 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %247 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %246, i32 0, i32 1
  %248 = load i32, i32* %247, align 4
  store i32 %248, i32* %14, align 4
  %249 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %250 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %249, i32 0, i32 1
  %251 = load i32, i32* %250, align 4
  %252 = load %struct.rbNode*, %struct.rbNode** %6, align 8
  %253 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %252, i32 0, i32 1
  store i32 %251, i32* %253, align 4
  %254 = load i32, i32* %14, align 4
  %255 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %256 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %255, i32 0, i32 1
  store i32 %254, i32* %256, align 4
  br label %257

257:                                              ; preds = %245, %157
  br label %258

258:                                              ; preds = %257, %107
  %259 = load i32, i32* %11, align 4
  %260 = icmp slt i32 %259, 1
  br i1 %260, label %261, label %262

261:                                              ; preds = %258
  br label %780

262:                                              ; preds = %258
  %263 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %264 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %263, i32 0, i32 1
  %265 = load i32, i32* %264, align 4
  %266 = icmp eq i32 %265, 1
  br i1 %266, label %267, label %780

267:                                              ; preds = %262
  br label %268

268:                                              ; preds = %267, %776
  %269 = load i32, i32* %11, align 4
  %270 = sub nsw i32 %269, 1
  %271 = sext i32 %270 to i64
  %272 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %271
  %273 = load %struct.rbNode*, %struct.rbNode** %272, align 8
  %274 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %273, i32 0, i32 2
  %275 = load i32, i32* %11, align 4
  %276 = sub nsw i32 %275, 1
  %277 = sext i32 %276 to i64
  %278 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %277
  %279 = load i32, i32* %278, align 4
  %280 = sext i32 %279 to i64
  %281 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %274, i64 0, i64 %280
  %282 = load %struct.rbNode*, %struct.rbNode** %281, align 8
  store %struct.rbNode* %282, %struct.rbNode** %7, align 8
  %283 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %284 = icmp ne %struct.rbNode* %283, null
  br i1 %284, label %285, label %293

285:                                              ; preds = %268
  %286 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %287 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %286, i32 0, i32 1
  %288 = load i32, i32* %287, align 4
  %289 = icmp eq i32 %288, 0
  br i1 %289, label %290, label %293

290:                                              ; preds = %285
  %291 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %292 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %291, i32 0, i32 1
  store i32 1, i32* %292, align 4
  br label %779

293:                                              ; preds = %285, %268
  %294 = load i32, i32* %11, align 4
  %295 = icmp slt i32 %294, 2
  br i1 %295, label %296, label %297

296:                                              ; preds = %293
  br label %779

297:                                              ; preds = %293
  %298 = load i32, i32* %11, align 4
  %299 = sub nsw i32 %298, 2
  %300 = sext i32 %299 to i64
  %301 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %300
  %302 = load i32, i32* %301, align 4
  %303 = icmp eq i32 %302, 0
  br i1 %303, label %304, label %540

304:                                              ; preds = %297
  %305 = load i32, i32* %11, align 4
  %306 = sub nsw i32 %305, 1
  %307 = sext i32 %306 to i64
  %308 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %307
  %309 = load %struct.rbNode*, %struct.rbNode** %308, align 8
  %310 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %309, i32 0, i32 2
  %311 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %310, i64 0, i64 1
  %312 = load %struct.rbNode*, %struct.rbNode** %311, align 8
  store %struct.rbNode* %312, %struct.rbNode** %9, align 8
  %313 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %314 = icmp eq %struct.rbNode* %313, null
  br i1 %314, label %315, label %316

315:                                              ; preds = %304
  br label %779

316:                                              ; preds = %304
  %317 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %318 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %317, i32 0, i32 1
  %319 = load i32, i32* %318, align 4
  %320 = icmp eq i32 %319, 0
  br i1 %320, label %321, label %400

321:                                              ; preds = %316
  %322 = load i32, i32* %11, align 4
  %323 = sub nsw i32 %322, 1
  %324 = sext i32 %323 to i64
  %325 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %324
  %326 = load %struct.rbNode*, %struct.rbNode** %325, align 8
  %327 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %326, i32 0, i32 1
  store i32 0, i32* %327, align 4
  %328 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %329 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %328, i32 0, i32 1
  store i32 1, i32* %329, align 4
  %330 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %331 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %330, i32 0, i32 2
  %332 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %331, i64 0, i64 0
  %333 = load %struct.rbNode*, %struct.rbNode** %332, align 8
  %334 = load i32, i32* %11, align 4
  %335 = sub nsw i32 %334, 1
  %336 = sext i32 %335 to i64
  %337 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %336
  %338 = load %struct.rbNode*, %struct.rbNode** %337, align 8
  %339 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %338, i32 0, i32 2
  %340 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %339, i64 0, i64 1
  store %struct.rbNode* %333, %struct.rbNode** %340, align 8
  %341 = load i32, i32* %11, align 4
  %342 = sub nsw i32 %341, 1
  %343 = sext i32 %342 to i64
  %344 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %343
  %345 = load %struct.rbNode*, %struct.rbNode** %344, align 8
  %346 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %347 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %346, i32 0, i32 2
  %348 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %347, i64 0, i64 0
  store %struct.rbNode* %345, %struct.rbNode** %348, align 8
  %349 = load i32, i32* %11, align 4
  %350 = sub nsw i32 %349, 1
  %351 = sext i32 %350 to i64
  %352 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %351
  %353 = load %struct.rbNode*, %struct.rbNode** %352, align 8
  %354 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %355 = icmp eq %struct.rbNode* %353, %354
  br i1 %355, label %356, label %358

356:                                              ; preds = %321
  %357 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  store %struct.rbNode* %357, %struct.rbNode** @root, align 8
  br label %373

358:                                              ; preds = %321
  %359 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %360 = load i32, i32* %11, align 4
  %361 = sub nsw i32 %360, 2
  %362 = sext i32 %361 to i64
  %363 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %362
  %364 = load %struct.rbNode*, %struct.rbNode** %363, align 8
  %365 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %364, i32 0, i32 2
  %366 = load i32, i32* %11, align 4
  %367 = sub nsw i32 %366, 2
  %368 = sext i32 %367 to i64
  %369 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %368
  %370 = load i32, i32* %369, align 4
  %371 = sext i32 %370 to i64
  %372 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %365, i64 0, i64 %371
  store %struct.rbNode* %359, %struct.rbNode** %372, align 8
  br label %373

373:                                              ; preds = %358, %356
  %374 = load i32, i32* %11, align 4
  %375 = sext i32 %374 to i64
  %376 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %375
  store i32 0, i32* %376, align 4
  %377 = load i32, i32* %11, align 4
  %378 = sub nsw i32 %377, 1
  %379 = sext i32 %378 to i64
  %380 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %379
  %381 = load %struct.rbNode*, %struct.rbNode** %380, align 8
  %382 = load i32, i32* %11, align 4
  %383 = sext i32 %382 to i64
  %384 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %383
  store %struct.rbNode* %381, %struct.rbNode** %384, align 8
  %385 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %386 = load i32, i32* %11, align 4
  %387 = sub nsw i32 %386, 1
  %388 = sext i32 %387 to i64
  %389 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %388
  store %struct.rbNode* %385, %struct.rbNode** %389, align 8
  %390 = load i32, i32* %11, align 4
  %391 = add nsw i32 %390, 1
  store i32 %391, i32* %11, align 4
  %392 = load i32, i32* %11, align 4
  %393 = sub nsw i32 %392, 1
  %394 = sext i32 %393 to i64
  %395 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %394
  %396 = load %struct.rbNode*, %struct.rbNode** %395, align 8
  %397 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %396, i32 0, i32 2
  %398 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %397, i64 0, i64 1
  %399 = load %struct.rbNode*, %struct.rbNode** %398, align 8
  store %struct.rbNode* %399, %struct.rbNode** %9, align 8
  br label %400

400:                                              ; preds = %373, %316
  %401 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %402 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %401, i32 0, i32 2
  %403 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %402, i64 0, i64 0
  %404 = load %struct.rbNode*, %struct.rbNode** %403, align 8
  %405 = icmp eq %struct.rbNode* %404, null
  br i1 %405, label %414, label %406

406:                                              ; preds = %400
  %407 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %408 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %407, i32 0, i32 2
  %409 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %408, i64 0, i64 0
  %410 = load %struct.rbNode*, %struct.rbNode** %409, align 8
  %411 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %410, i32 0, i32 1
  %412 = load i32, i32* %411, align 4
  %413 = icmp eq i32 %412, 1
  br i1 %413, label %414, label %431

414:                                              ; preds = %406, %400
  %415 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %416 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %415, i32 0, i32 2
  %417 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %416, i64 0, i64 1
  %418 = load %struct.rbNode*, %struct.rbNode** %417, align 8
  %419 = icmp eq %struct.rbNode* %418, null
  br i1 %419, label %428, label %420

420:                                              ; preds = %414
  %421 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %422 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %421, i32 0, i32 2
  %423 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %422, i64 0, i64 1
  %424 = load %struct.rbNode*, %struct.rbNode** %423, align 8
  %425 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %424, i32 0, i32 1
  %426 = load i32, i32* %425, align 4
  %427 = icmp eq i32 %426, 1
  br i1 %427, label %428, label %431

428:                                              ; preds = %420, %414
  %429 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %430 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %429, i32 0, i32 1
  store i32 0, i32* %430, align 4
  br label %539

431:                                              ; preds = %420, %406
  %432 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %433 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %432, i32 0, i32 2
  %434 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %433, i64 0, i64 1
  %435 = load %struct.rbNode*, %struct.rbNode** %434, align 8
  %436 = icmp eq %struct.rbNode* %435, null
  br i1 %436, label %445, label %437

437:                                              ; preds = %431
  %438 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %439 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %438, i32 0, i32 2
  %440 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %439, i64 0, i64 1
  %441 = load %struct.rbNode*, %struct.rbNode** %440, align 8
  %442 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %441, i32 0, i32 1
  %443 = load i32, i32* %442, align 4
  %444 = icmp eq i32 %443, 1
  br i1 %444, label %445, label %474

445:                                              ; preds = %437, %431
  %446 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %447 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %446, i32 0, i32 2
  %448 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %447, i64 0, i64 0
  %449 = load %struct.rbNode*, %struct.rbNode** %448, align 8
  store %struct.rbNode* %449, %struct.rbNode** %8, align 8
  %450 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %451 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %450, i32 0, i32 1
  store i32 0, i32* %451, align 4
  %452 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %453 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %452, i32 0, i32 1
  store i32 1, i32* %453, align 4
  %454 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %455 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %454, i32 0, i32 2
  %456 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %455, i64 0, i64 1
  %457 = load %struct.rbNode*, %struct.rbNode** %456, align 8
  %458 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %459 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %458, i32 0, i32 2
  %460 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %459, i64 0, i64 0
  store %struct.rbNode* %457, %struct.rbNode** %460, align 8
  %461 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %462 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %463 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %462, i32 0, i32 2
  %464 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %463, i64 0, i64 1
  store %struct.rbNode* %461, %struct.rbNode** %464, align 8
  %465 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %466 = load i32, i32* %11, align 4
  %467 = sub nsw i32 %466, 1
  %468 = sext i32 %467 to i64
  %469 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %468
  %470 = load %struct.rbNode*, %struct.rbNode** %469, align 8
  %471 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %470, i32 0, i32 2
  %472 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %471, i64 0, i64 1
  store %struct.rbNode* %465, %struct.rbNode** %472, align 8
  %473 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  store %struct.rbNode* %473, %struct.rbNode** %9, align 8
  br label %474

474:                                              ; preds = %445, %437
  %475 = load i32, i32* %11, align 4
  %476 = sub nsw i32 %475, 1
  %477 = sext i32 %476 to i64
  %478 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %477
  %479 = load %struct.rbNode*, %struct.rbNode** %478, align 8
  %480 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %479, i32 0, i32 1
  %481 = load i32, i32* %480, align 4
  %482 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %483 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %482, i32 0, i32 1
  store i32 %481, i32* %483, align 4
  %484 = load i32, i32* %11, align 4
  %485 = sub nsw i32 %484, 1
  %486 = sext i32 %485 to i64
  %487 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %486
  %488 = load %struct.rbNode*, %struct.rbNode** %487, align 8
  %489 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %488, i32 0, i32 1
  store i32 1, i32* %489, align 4
  %490 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %491 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %490, i32 0, i32 2
  %492 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %491, i64 0, i64 1
  %493 = load %struct.rbNode*, %struct.rbNode** %492, align 8
  %494 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %493, i32 0, i32 1
  store i32 1, i32* %494, align 4
  %495 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %496 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %495, i32 0, i32 2
  %497 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %496, i64 0, i64 0
  %498 = load %struct.rbNode*, %struct.rbNode** %497, align 8
  %499 = load i32, i32* %11, align 4
  %500 = sub nsw i32 %499, 1
  %501 = sext i32 %500 to i64
  %502 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %501
  %503 = load %struct.rbNode*, %struct.rbNode** %502, align 8
  %504 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %503, i32 0, i32 2
  %505 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %504, i64 0, i64 1
  store %struct.rbNode* %498, %struct.rbNode** %505, align 8
  %506 = load i32, i32* %11, align 4
  %507 = sub nsw i32 %506, 1
  %508 = sext i32 %507 to i64
  %509 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %508
  %510 = load %struct.rbNode*, %struct.rbNode** %509, align 8
  %511 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %512 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %511, i32 0, i32 2
  %513 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %512, i64 0, i64 0
  store %struct.rbNode* %510, %struct.rbNode** %513, align 8
  %514 = load i32, i32* %11, align 4
  %515 = sub nsw i32 %514, 1
  %516 = sext i32 %515 to i64
  %517 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %516
  %518 = load %struct.rbNode*, %struct.rbNode** %517, align 8
  %519 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %520 = icmp eq %struct.rbNode* %518, %519
  br i1 %520, label %521, label %523

521:                                              ; preds = %474
  %522 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  store %struct.rbNode* %522, %struct.rbNode** @root, align 8
  br label %538

523:                                              ; preds = %474
  %524 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %525 = load i32, i32* %11, align 4
  %526 = sub nsw i32 %525, 2
  %527 = sext i32 %526 to i64
  %528 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %527
  %529 = load %struct.rbNode*, %struct.rbNode** %528, align 8
  %530 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %529, i32 0, i32 2
  %531 = load i32, i32* %11, align 4
  %532 = sub nsw i32 %531, 2
  %533 = sext i32 %532 to i64
  %534 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %533
  %535 = load i32, i32* %534, align 4
  %536 = sext i32 %535 to i64
  %537 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %530, i64 0, i64 %536
  store %struct.rbNode* %524, %struct.rbNode** %537, align 8
  br label %538

538:                                              ; preds = %523, %521
  br label %779

539:                                              ; preds = %428
  br label %776

540:                                              ; preds = %297
  %541 = load i32, i32* %11, align 4
  %542 = sub nsw i32 %541, 1
  %543 = sext i32 %542 to i64
  %544 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %543
  %545 = load %struct.rbNode*, %struct.rbNode** %544, align 8
  %546 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %545, i32 0, i32 2
  %547 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %546, i64 0, i64 0
  %548 = load %struct.rbNode*, %struct.rbNode** %547, align 8
  store %struct.rbNode* %548, %struct.rbNode** %9, align 8
  %549 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %550 = icmp eq %struct.rbNode* %549, null
  br i1 %550, label %551, label %552

551:                                              ; preds = %540
  br label %779

552:                                              ; preds = %540
  %553 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %554 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %553, i32 0, i32 1
  %555 = load i32, i32* %554, align 4
  %556 = icmp eq i32 %555, 0
  br i1 %556, label %557, label %636

557:                                              ; preds = %552
  %558 = load i32, i32* %11, align 4
  %559 = sub nsw i32 %558, 1
  %560 = sext i32 %559 to i64
  %561 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %560
  %562 = load %struct.rbNode*, %struct.rbNode** %561, align 8
  %563 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %562, i32 0, i32 1
  store i32 0, i32* %563, align 4
  %564 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %565 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %564, i32 0, i32 1
  store i32 1, i32* %565, align 4
  %566 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %567 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %566, i32 0, i32 2
  %568 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %567, i64 0, i64 1
  %569 = load %struct.rbNode*, %struct.rbNode** %568, align 8
  %570 = load i32, i32* %11, align 4
  %571 = sub nsw i32 %570, 1
  %572 = sext i32 %571 to i64
  %573 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %572
  %574 = load %struct.rbNode*, %struct.rbNode** %573, align 8
  %575 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %574, i32 0, i32 2
  %576 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %575, i64 0, i64 0
  store %struct.rbNode* %569, %struct.rbNode** %576, align 8
  %577 = load i32, i32* %11, align 4
  %578 = sub nsw i32 %577, 1
  %579 = sext i32 %578 to i64
  %580 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %579
  %581 = load %struct.rbNode*, %struct.rbNode** %580, align 8
  %582 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %583 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %582, i32 0, i32 2
  %584 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %583, i64 0, i64 1
  store %struct.rbNode* %581, %struct.rbNode** %584, align 8
  %585 = load i32, i32* %11, align 4
  %586 = sub nsw i32 %585, 1
  %587 = sext i32 %586 to i64
  %588 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %587
  %589 = load %struct.rbNode*, %struct.rbNode** %588, align 8
  %590 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %591 = icmp eq %struct.rbNode* %589, %590
  br i1 %591, label %592, label %594

592:                                              ; preds = %557
  %593 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  store %struct.rbNode* %593, %struct.rbNode** @root, align 8
  br label %609

594:                                              ; preds = %557
  %595 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %596 = load i32, i32* %11, align 4
  %597 = sub nsw i32 %596, 2
  %598 = sext i32 %597 to i64
  %599 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %598
  %600 = load %struct.rbNode*, %struct.rbNode** %599, align 8
  %601 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %600, i32 0, i32 2
  %602 = load i32, i32* %11, align 4
  %603 = sub nsw i32 %602, 2
  %604 = sext i32 %603 to i64
  %605 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %604
  %606 = load i32, i32* %605, align 4
  %607 = sext i32 %606 to i64
  %608 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %601, i64 0, i64 %607
  store %struct.rbNode* %595, %struct.rbNode** %608, align 8
  br label %609

609:                                              ; preds = %594, %592
  %610 = load i32, i32* %11, align 4
  %611 = sext i32 %610 to i64
  %612 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %611
  store i32 1, i32* %612, align 4
  %613 = load i32, i32* %11, align 4
  %614 = sub nsw i32 %613, 1
  %615 = sext i32 %614 to i64
  %616 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %615
  %617 = load %struct.rbNode*, %struct.rbNode** %616, align 8
  %618 = load i32, i32* %11, align 4
  %619 = sext i32 %618 to i64
  %620 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %619
  store %struct.rbNode* %617, %struct.rbNode** %620, align 8
  %621 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %622 = load i32, i32* %11, align 4
  %623 = sub nsw i32 %622, 1
  %624 = sext i32 %623 to i64
  %625 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %624
  store %struct.rbNode* %621, %struct.rbNode** %625, align 8
  %626 = load i32, i32* %11, align 4
  %627 = add nsw i32 %626, 1
  store i32 %627, i32* %11, align 4
  %628 = load i32, i32* %11, align 4
  %629 = sub nsw i32 %628, 1
  %630 = sext i32 %629 to i64
  %631 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %630
  %632 = load %struct.rbNode*, %struct.rbNode** %631, align 8
  %633 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %632, i32 0, i32 2
  %634 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %633, i64 0, i64 0
  %635 = load %struct.rbNode*, %struct.rbNode** %634, align 8
  store %struct.rbNode* %635, %struct.rbNode** %9, align 8
  br label %636

636:                                              ; preds = %609, %552
  %637 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %638 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %637, i32 0, i32 2
  %639 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %638, i64 0, i64 0
  %640 = load %struct.rbNode*, %struct.rbNode** %639, align 8
  %641 = icmp ne %struct.rbNode* %640, null
  br i1 %641, label %642, label %650

642:                                              ; preds = %636
  %643 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %644 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %643, i32 0, i32 2
  %645 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %644, i64 0, i64 0
  %646 = load %struct.rbNode*, %struct.rbNode** %645, align 8
  %647 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %646, i32 0, i32 1
  %648 = load i32, i32* %647, align 4
  %649 = icmp eq i32 %648, 1
  br i1 %649, label %650, label %667

650:                                              ; preds = %642, %636
  %651 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %652 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %651, i32 0, i32 2
  %653 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %652, i64 0, i64 1
  %654 = load %struct.rbNode*, %struct.rbNode** %653, align 8
  %655 = icmp ne %struct.rbNode* %654, null
  br i1 %655, label %656, label %664

656:                                              ; preds = %650
  %657 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %658 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %657, i32 0, i32 2
  %659 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %658, i64 0, i64 1
  %660 = load %struct.rbNode*, %struct.rbNode** %659, align 8
  %661 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %660, i32 0, i32 1
  %662 = load i32, i32* %661, align 4
  %663 = icmp eq i32 %662, 1
  br i1 %663, label %664, label %667

664:                                              ; preds = %656, %650
  %665 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %666 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %665, i32 0, i32 1
  store i32 0, i32* %666, align 4
  br label %775

667:                                              ; preds = %656, %642
  %668 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %669 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %668, i32 0, i32 2
  %670 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %669, i64 0, i64 0
  %671 = load %struct.rbNode*, %struct.rbNode** %670, align 8
  %672 = icmp ne %struct.rbNode* %671, null
  br i1 %672, label %673, label %681

673:                                              ; preds = %667
  %674 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %675 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %674, i32 0, i32 2
  %676 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %675, i64 0, i64 0
  %677 = load %struct.rbNode*, %struct.rbNode** %676, align 8
  %678 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %677, i32 0, i32 1
  %679 = load i32, i32* %678, align 4
  %680 = icmp eq i32 %679, 1
  br i1 %680, label %681, label %710

681:                                              ; preds = %673, %667
  %682 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %683 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %682, i32 0, i32 2
  %684 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %683, i64 0, i64 1
  %685 = load %struct.rbNode*, %struct.rbNode** %684, align 8
  store %struct.rbNode* %685, %struct.rbNode** %8, align 8
  %686 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %687 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %686, i32 0, i32 1
  store i32 0, i32* %687, align 4
  %688 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %689 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %688, i32 0, i32 1
  store i32 1, i32* %689, align 4
  %690 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %691 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %690, i32 0, i32 2
  %692 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %691, i64 0, i64 0
  %693 = load %struct.rbNode*, %struct.rbNode** %692, align 8
  %694 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %695 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %694, i32 0, i32 2
  %696 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %695, i64 0, i64 1
  store %struct.rbNode* %693, %struct.rbNode** %696, align 8
  %697 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %698 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %699 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %698, i32 0, i32 2
  %700 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %699, i64 0, i64 0
  store %struct.rbNode* %697, %struct.rbNode** %700, align 8
  %701 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %702 = load i32, i32* %11, align 4
  %703 = sub nsw i32 %702, 1
  %704 = sext i32 %703 to i64
  %705 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %704
  %706 = load %struct.rbNode*, %struct.rbNode** %705, align 8
  %707 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %706, i32 0, i32 2
  %708 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %707, i64 0, i64 0
  store %struct.rbNode* %701, %struct.rbNode** %708, align 8
  %709 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  store %struct.rbNode* %709, %struct.rbNode** %9, align 8
  br label %710

710:                                              ; preds = %681, %673
  %711 = load i32, i32* %11, align 4
  %712 = sub nsw i32 %711, 1
  %713 = sext i32 %712 to i64
  %714 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %713
  %715 = load %struct.rbNode*, %struct.rbNode** %714, align 8
  %716 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %715, i32 0, i32 1
  %717 = load i32, i32* %716, align 4
  %718 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %719 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %718, i32 0, i32 1
  store i32 %717, i32* %719, align 4
  %720 = load i32, i32* %11, align 4
  %721 = sub nsw i32 %720, 1
  %722 = sext i32 %721 to i64
  %723 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %722
  %724 = load %struct.rbNode*, %struct.rbNode** %723, align 8
  %725 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %724, i32 0, i32 1
  store i32 1, i32* %725, align 4
  %726 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %727 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %726, i32 0, i32 2
  %728 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %727, i64 0, i64 0
  %729 = load %struct.rbNode*, %struct.rbNode** %728, align 8
  %730 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %729, i32 0, i32 1
  store i32 1, i32* %730, align 4
  %731 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %732 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %731, i32 0, i32 2
  %733 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %732, i64 0, i64 1
  %734 = load %struct.rbNode*, %struct.rbNode** %733, align 8
  %735 = load i32, i32* %11, align 4
  %736 = sub nsw i32 %735, 1
  %737 = sext i32 %736 to i64
  %738 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %737
  %739 = load %struct.rbNode*, %struct.rbNode** %738, align 8
  %740 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %739, i32 0, i32 2
  %741 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %740, i64 0, i64 0
  store %struct.rbNode* %734, %struct.rbNode** %741, align 8
  %742 = load i32, i32* %11, align 4
  %743 = sub nsw i32 %742, 1
  %744 = sext i32 %743 to i64
  %745 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %744
  %746 = load %struct.rbNode*, %struct.rbNode** %745, align 8
  %747 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %748 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %747, i32 0, i32 2
  %749 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %748, i64 0, i64 1
  store %struct.rbNode* %746, %struct.rbNode** %749, align 8
  %750 = load i32, i32* %11, align 4
  %751 = sub nsw i32 %750, 1
  %752 = sext i32 %751 to i64
  %753 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %752
  %754 = load %struct.rbNode*, %struct.rbNode** %753, align 8
  %755 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %756 = icmp eq %struct.rbNode* %754, %755
  br i1 %756, label %757, label %759

757:                                              ; preds = %710
  %758 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  store %struct.rbNode* %758, %struct.rbNode** @root, align 8
  br label %774

759:                                              ; preds = %710
  %760 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %761 = load i32, i32* %11, align 4
  %762 = sub nsw i32 %761, 2
  %763 = sext i32 %762 to i64
  %764 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %763
  %765 = load %struct.rbNode*, %struct.rbNode** %764, align 8
  %766 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %765, i32 0, i32 2
  %767 = load i32, i32* %11, align 4
  %768 = sub nsw i32 %767, 2
  %769 = sext i32 %768 to i64
  %770 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %769
  %771 = load i32, i32* %770, align 4
  %772 = sext i32 %771 to i64
  %773 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %766, i64 0, i64 %772
  store %struct.rbNode* %760, %struct.rbNode** %773, align 8
  br label %774

774:                                              ; preds = %759, %757
  br label %779

775:                                              ; preds = %664
  br label %776

776:                                              ; preds = %775, %539
  %777 = load i32, i32* %11, align 4
  %778 = sub nsw i32 %777, 1
  store i32 %778, i32* %11, align 4
  br label %268

779:                                              ; preds = %774, %551, %538, %315, %296, %290
  br label %780

780:                                              ; preds = %17, %261, %779, %262
  ret void
}

declare void @free(i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @inorderTraversal(%struct.rbNode* %0) #0 {
  %2 = alloca %struct.rbNode*, align 8
  store %struct.rbNode* %0, %struct.rbNode** %2, align 8
  %3 = load %struct.rbNode*, %struct.rbNode** %2, align 8
  %4 = icmp ne %struct.rbNode* %3, null
  br i1 %4, label %5, label %18

5:                                                ; preds = %1
  %6 = load %struct.rbNode*, %struct.rbNode** %2, align 8
  %7 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %6, i32 0, i32 0
  %8 = load i32, i32* %7, align 8
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i64 0, i64 0), i32 %8)
  %10 = load %struct.rbNode*, %struct.rbNode** %2, align 8
  %11 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %10, i32 0, i32 2
  %12 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %11, i64 0, i64 0
  %13 = load %struct.rbNode*, %struct.rbNode** %12, align 8
  call void @inorderTraversal(%struct.rbNode* %13)
  %14 = load %struct.rbNode*, %struct.rbNode** %2, align 8
  %15 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %14, i32 0, i32 2
  %16 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %15, i64 0, i64 1
  %17 = load %struct.rbNode*, %struct.rbNode** %16, align 8
  call void @inorderTraversal(%struct.rbNode* %17)
  br label %18

18:                                               ; preds = %5, %1
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 -1, i32* %2, align 4
  store i32 -1, i32* %3, align 4
  br label %4

4:                                                ; preds = %0, %39
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.28, i64 0, i64 0))
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.29, i64 0, i64 0))
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.30, i64 0, i64 0))
  %8 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.31, i64 0, i64 0), i32* %2)
  %9 = load i32, i32* %2, align 4
  %10 = icmp eq i32 %9, 1
  br i1 %10, label %11, label %17

11:                                               ; preds = %4
  %12 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.32, i64 0, i64 0))
  %13 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.31, i64 0, i64 0), i32* %3)
  %14 = load i32, i32* %3, align 4
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.33, i64 0, i64 0), i32 %14)
  %16 = load i32, i32* %3, align 4
  call void @insertion(i32 %16)
  br label %39

17:                                               ; preds = %4
  %18 = load i32, i32* %2, align 4
  %19 = icmp eq i32 %18, 2
  br i1 %19, label %20, label %24

20:                                               ; preds = %17
  %21 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.34, i64 0, i64 0))
  %22 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.31, i64 0, i64 0), i32* %3)
  %23 = load i32, i32* %3, align 4
  call void @deletion(i32 %23)
  br label %38

24:                                               ; preds = %17
  %25 = load i32, i32* %2, align 4
  %26 = icmp eq i32 %25, 3
  br i1 %26, label %27, label %30

27:                                               ; preds = %24
  %28 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  call void @inorderTraversal(%struct.rbNode* %28)
  %29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.35, i64 0, i64 0))
  br label %37

30:                                               ; preds = %24
  %31 = load i32, i32* %2, align 4
  %32 = icmp eq i32 %31, 4
  br i1 %32, label %33, label %34

33:                                               ; preds = %30
  br label %41

34:                                               ; preds = %30
  %35 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.36, i64 0, i64 0))
  br label %36

36:                                               ; preds = %34
  br label %37

37:                                               ; preds = %36, %27
  br label %38

38:                                               ; preds = %37, %20
  br label %39

39:                                               ; preds = %38, %11
  %40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([66 x i8], [66 x i8]* @.str.37, i64 0, i64 0))
  br label %4

41:                                               ; preds = %33
  ret i32 0
}

declare i32 @scanf(i8*, ...) #2

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { allocsize(0) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="non-leaf" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "probe-stack"="__chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="apple-a12" "target-features"="+aes,+crc,+crypto,+fp-armv8,+fullfp16,+lse,+neon,+ras,+rcpc,+rdm,+sha2,+v8.3a,+zcm,+zcz" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { allocsize(0) }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 11, i32 3]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"Apple clang version 12.0.5 (clang-1205.0.22.9)"}
