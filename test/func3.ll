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
  store %struct.rbNode* %15, %struct.rbNode** %4, align 8
  %16 = load %struct.rbNode*, %struct.rbNode** %4, align 8
  %17 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %16, i32 0, i32 1
  %18 = load i32, i32* %17, align 4
  %19 = icmp eq i32 %18, 1
  br i1 %19, label %20, label %297

20:                                               ; preds = %1
  br label %21

21:                                               ; preds = %20, %293
  %22 = load i32, i32* %11, align 4
  %23 = sub nsw i32 %22, 1
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %24
  %26 = load %struct.rbNode*, %struct.rbNode** %25, align 8
  %27 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %26, i32 0, i32 2
  %28 = load i32, i32* %11, align 4
  %29 = sub nsw i32 %28, 1
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %30
  %32 = load i32, i32* %31, align 4
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %27, i64 0, i64 %33
  %35 = load %struct.rbNode*, %struct.rbNode** %34, align 8
  store %struct.rbNode* %35, %struct.rbNode** %7, align 8
  %36 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %37 = icmp ne %struct.rbNode* %36, null
  br i1 %37, label %38, label %46

38:                                               ; preds = %21
  %39 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %40 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %39, i32 0, i32 1
  %41 = load i32, i32* %40, align 4
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %43, label %46

43:                                               ; preds = %38
  %44 = load %struct.rbNode*, %struct.rbNode** %7, align 8
  %45 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %44, i32 0, i32 1
  store i32 1, i32* %45, align 4
  br label %296

46:                                               ; preds = %38, %21
  %47 = load i32, i32* %11, align 4
  %48 = icmp slt i32 %47, 2
  br i1 %48, label %49, label %50

49:                                               ; preds = %46
  br label %296

50:                                               ; preds = %46
  %51 = load i32, i32* %11, align 4
  %52 = sub nsw i32 %51, 2
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %53
  %55 = load i32, i32* %54, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %57, label %293

57:                                               ; preds = %50
  %58 = load i32, i32* %11, align 4
  %59 = sub nsw i32 %58, 1
  %60 = sext i32 %59 to i64
  %61 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %60
  %62 = load %struct.rbNode*, %struct.rbNode** %61, align 8
  %63 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %62, i32 0, i32 2
  %64 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %63, i64 0, i64 1
  %65 = load %struct.rbNode*, %struct.rbNode** %64, align 8
  store %struct.rbNode* %65, %struct.rbNode** %9, align 8
  %66 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %67 = icmp eq %struct.rbNode* %66, null
  br i1 %67, label %68, label %69

68:                                               ; preds = %57
  br label %296

69:                                               ; preds = %57
  %70 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %71 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %70, i32 0, i32 1
  %72 = load i32, i32* %71, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %74, label %153

74:                                               ; preds = %69
  %75 = load i32, i32* %11, align 4
  %76 = sub nsw i32 %75, 1
  %77 = sext i32 %76 to i64
  %78 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %77
  %79 = load %struct.rbNode*, %struct.rbNode** %78, align 8
  %80 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %79, i32 0, i32 1
  store i32 0, i32* %80, align 4
  %81 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %82 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %81, i32 0, i32 1
  store i32 1, i32* %82, align 4
  %83 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %84 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %83, i32 0, i32 2
  %85 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %84, i64 0, i64 0
  %86 = load %struct.rbNode*, %struct.rbNode** %85, align 8
  %87 = load i32, i32* %11, align 4
  %88 = sub nsw i32 %87, 1
  %89 = sext i32 %88 to i64
  %90 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %89
  %91 = load %struct.rbNode*, %struct.rbNode** %90, align 8
  %92 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %91, i32 0, i32 2
  %93 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %92, i64 0, i64 1
  store %struct.rbNode* %86, %struct.rbNode** %93, align 8
  %94 = load i32, i32* %11, align 4
  %95 = sub nsw i32 %94, 1
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %96
  %98 = load %struct.rbNode*, %struct.rbNode** %97, align 8
  %99 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %100 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %99, i32 0, i32 2
  %101 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %100, i64 0, i64 0
  store %struct.rbNode* %98, %struct.rbNode** %101, align 8
  %102 = load i32, i32* %11, align 4
  %103 = sub nsw i32 %102, 1
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %104
  %106 = load %struct.rbNode*, %struct.rbNode** %105, align 8
  %107 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %108 = icmp eq %struct.rbNode* %106, %107
  br i1 %108, label %109, label %111

109:                                              ; preds = %74
  %110 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  store %struct.rbNode* %110, %struct.rbNode** @root, align 8
  br label %126

111:                                              ; preds = %74
  %112 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %113 = load i32, i32* %11, align 4
  %114 = sub nsw i32 %113, 2
  %115 = sext i32 %114 to i64
  %116 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %115
  %117 = load %struct.rbNode*, %struct.rbNode** %116, align 8
  %118 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %117, i32 0, i32 2
  %119 = load i32, i32* %11, align 4
  %120 = sub nsw i32 %119, 2
  %121 = sext i32 %120 to i64
  %122 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %121
  %123 = load i32, i32* %122, align 4
  %124 = sext i32 %123 to i64
  %125 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %118, i64 0, i64 %124
  store %struct.rbNode* %112, %struct.rbNode** %125, align 8
  br label %126

126:                                              ; preds = %111, %109
  %127 = load i32, i32* %11, align 4
  %128 = sext i32 %127 to i64
  %129 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %128
  store i32 0, i32* %129, align 4
  %130 = load i32, i32* %11, align 4
  %131 = sub nsw i32 %130, 1
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %132
  %134 = load %struct.rbNode*, %struct.rbNode** %133, align 8
  %135 = load i32, i32* %11, align 4
  %136 = sext i32 %135 to i64
  %137 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %136
  store %struct.rbNode* %134, %struct.rbNode** %137, align 8
  %138 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %139 = load i32, i32* %11, align 4
  %140 = sub nsw i32 %139, 1
  %141 = sext i32 %140 to i64
  %142 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %141
  store %struct.rbNode* %138, %struct.rbNode** %142, align 8
  %143 = load i32, i32* %11, align 4
  %144 = add nsw i32 %143, 1
  store i32 %144, i32* %11, align 4
  %145 = load i32, i32* %11, align 4
  %146 = sub nsw i32 %145, 1
  %147 = sext i32 %146 to i64
  %148 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %147
  %149 = load %struct.rbNode*, %struct.rbNode** %148, align 8
  %150 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %149, i32 0, i32 2
  %151 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %150, i64 0, i64 1
  %152 = load %struct.rbNode*, %struct.rbNode** %151, align 8
  store %struct.rbNode* %152, %struct.rbNode** %9, align 8
  br label %153

153:                                              ; preds = %126, %69
  %154 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %155 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %154, i32 0, i32 2
  %156 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %155, i64 0, i64 0
  %157 = load %struct.rbNode*, %struct.rbNode** %156, align 8
  %158 = icmp eq %struct.rbNode* %157, null
  br i1 %158, label %167, label %159

159:                                              ; preds = %153
  %160 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %161 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %160, i32 0, i32 2
  %162 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %161, i64 0, i64 0
  %163 = load %struct.rbNode*, %struct.rbNode** %162, align 8
  %164 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %163, i32 0, i32 1
  %165 = load i32, i32* %164, align 4
  %166 = icmp eq i32 %165, 1
  br i1 %166, label %167, label %184

167:                                              ; preds = %159, %153
  %168 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %169 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %168, i32 0, i32 2
  %170 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %169, i64 0, i64 1
  %171 = load %struct.rbNode*, %struct.rbNode** %170, align 8
  %172 = icmp eq %struct.rbNode* %171, null
  br i1 %172, label %181, label %173

173:                                              ; preds = %167
  %174 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %175 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %174, i32 0, i32 2
  %176 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %175, i64 0, i64 1
  %177 = load %struct.rbNode*, %struct.rbNode** %176, align 8
  %178 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %177, i32 0, i32 1
  %179 = load i32, i32* %178, align 4
  %180 = icmp eq i32 %179, 1
  br i1 %180, label %181, label %184

181:                                              ; preds = %173, %167
  %182 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %183 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %182, i32 0, i32 1
  store i32 0, i32* %183, align 4
  br label %292

184:                                              ; preds = %173, %159
  %185 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %186 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %185, i32 0, i32 2
  %187 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %186, i64 0, i64 1
  %188 = load %struct.rbNode*, %struct.rbNode** %187, align 8
  %189 = icmp eq %struct.rbNode* %188, null
  br i1 %189, label %198, label %190

190:                                              ; preds = %184
  %191 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %192 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %191, i32 0, i32 2
  %193 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %192, i64 0, i64 1
  %194 = load %struct.rbNode*, %struct.rbNode** %193, align 8
  %195 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %194, i32 0, i32 1
  %196 = load i32, i32* %195, align 4
  %197 = icmp eq i32 %196, 1
  br i1 %197, label %198, label %227

198:                                              ; preds = %190, %184
  %199 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %200 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %199, i32 0, i32 2
  %201 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %200, i64 0, i64 0
  %202 = load %struct.rbNode*, %struct.rbNode** %201, align 8
  store %struct.rbNode* %202, %struct.rbNode** %8, align 8
  %203 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %204 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %203, i32 0, i32 1
  store i32 0, i32* %204, align 4
  %205 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %206 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %205, i32 0, i32 1
  store i32 1, i32* %206, align 4
  %207 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %208 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %207, i32 0, i32 2
  %209 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %208, i64 0, i64 1
  %210 = load %struct.rbNode*, %struct.rbNode** %209, align 8
  %211 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %212 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %211, i32 0, i32 2
  %213 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %212, i64 0, i64 0
  store %struct.rbNode* %210, %struct.rbNode** %213, align 8
  %214 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %215 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %216 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %215, i32 0, i32 2
  %217 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %216, i64 0, i64 1
  store %struct.rbNode* %214, %struct.rbNode** %217, align 8
  %218 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  %219 = load i32, i32* %11, align 4
  %220 = sub nsw i32 %219, 1
  %221 = sext i32 %220 to i64
  %222 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %221
  %223 = load %struct.rbNode*, %struct.rbNode** %222, align 8
  %224 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %223, i32 0, i32 2
  %225 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %224, i64 0, i64 1
  store %struct.rbNode* %218, %struct.rbNode** %225, align 8
  %226 = load %struct.rbNode*, %struct.rbNode** %8, align 8
  store %struct.rbNode* %226, %struct.rbNode** %9, align 8
  br label %227

227:                                              ; preds = %198, %190
  %228 = load i32, i32* %11, align 4
  %229 = sub nsw i32 %228, 1
  %230 = sext i32 %229 to i64
  %231 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %230
  %232 = load %struct.rbNode*, %struct.rbNode** %231, align 8
  %233 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %232, i32 0, i32 1
  %234 = load i32, i32* %233, align 4
  %235 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %236 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %235, i32 0, i32 1
  store i32 %234, i32* %236, align 4
  %237 = load i32, i32* %11, align 4
  %238 = sub nsw i32 %237, 1
  %239 = sext i32 %238 to i64
  %240 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %239
  %241 = load %struct.rbNode*, %struct.rbNode** %240, align 8
  %242 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %241, i32 0, i32 1
  store i32 1, i32* %242, align 4
  %243 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %244 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %243, i32 0, i32 2
  %245 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %244, i64 0, i64 1
  %246 = load %struct.rbNode*, %struct.rbNode** %245, align 8
  %247 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %246, i32 0, i32 1
  store i32 1, i32* %247, align 4
  %248 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %249 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %248, i32 0, i32 2
  %250 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %249, i64 0, i64 0
  %251 = load %struct.rbNode*, %struct.rbNode** %250, align 8
  %252 = load i32, i32* %11, align 4
  %253 = sub nsw i32 %252, 1
  %254 = sext i32 %253 to i64
  %255 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %254
  %256 = load %struct.rbNode*, %struct.rbNode** %255, align 8
  %257 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %256, i32 0, i32 2
  %258 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %257, i64 0, i64 1
  store %struct.rbNode* %251, %struct.rbNode** %258, align 8
  %259 = load i32, i32* %11, align 4
  %260 = sub nsw i32 %259, 1
  %261 = sext i32 %260 to i64
  %262 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %261
  %263 = load %struct.rbNode*, %struct.rbNode** %262, align 8
  %264 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %265 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %264, i32 0, i32 2
  %266 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %265, i64 0, i64 0
  store %struct.rbNode* %263, %struct.rbNode** %266, align 8
  %267 = load i32, i32* %11, align 4
  %268 = sub nsw i32 %267, 1
  %269 = sext i32 %268 to i64
  %270 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %269
  %271 = load %struct.rbNode*, %struct.rbNode** %270, align 8
  %272 = load %struct.rbNode*, %struct.rbNode** @root, align 8
  %273 = icmp eq %struct.rbNode* %271, %272
  br i1 %273, label %274, label %276

274:                                              ; preds = %227
  %275 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  store %struct.rbNode* %275, %struct.rbNode** @root, align 8
  br label %291

276:                                              ; preds = %227
  %277 = load %struct.rbNode*, %struct.rbNode** %9, align 8
  %278 = load i32, i32* %11, align 4
  %279 = sub nsw i32 %278, 2
  %280 = sext i32 %279 to i64
  %281 = getelementptr inbounds [98 x %struct.rbNode*], [98 x %struct.rbNode*]* %3, i64 0, i64 %280
  %282 = load %struct.rbNode*, %struct.rbNode** %281, align 8
  %283 = getelementptr inbounds %struct.rbNode, %struct.rbNode* %282, i32 0, i32 2
  %284 = load i32, i32* %11, align 4
  %285 = sub nsw i32 %284, 2
  %286 = sext i32 %285 to i64
  %287 = getelementptr inbounds [98 x i32], [98 x i32]* %10, i64 0, i64 %286
  %288 = load i32, i32* %287, align 4
  %289 = sext i32 %288 to i64
  %290 = getelementptr inbounds [2 x %struct.rbNode*], [2 x %struct.rbNode*]* %283, i64 0, i64 %289
  store %struct.rbNode* %277, %struct.rbNode** %290, align 8
  br label %291

291:                                              ; preds = %276, %274
  br label %296

292:                                              ; preds = %181
  br label %293

293:                                              ; preds = %292, %50
  %294 = load i32, i32* %11, align 4
  %295 = sub nsw i32 %294, 1
  store i32 %295, i32* %11, align 4
  br label %21

296:                                              ; preds = %291, %68, %49, %43
  br label %297

297:                                              ; preds = %296, %1
  ret void
}