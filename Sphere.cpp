#include "Sphere.h"

const float PI = 3.1415926;

Sphere_A::Sphere_A(int precision) {
	init(precision);
}

float Sphere_A::toRadians(float degrees) {
	return (degrees * PI) / 180;
}

/*
球体保存以下信息：
	顶点坐标
	法线向量
	纹理坐标
	顶点索引
*/

void Sphere_A::init(int precision) {
	mNumVertices = (precision + 1) * (precision + 1);
	mNumIndices = precision * precision * 6;
	mVertices.resize(mNumVertices);
	mNormals.resize(mNumVertices);
	mTexCoords.resize(mNumVertices);
	mIndices.resize(mNumIndices);

	for (int i = 0; i <= precision; i++) {
		for (int j = 0; j <= precision; j++) {
			float y = static_cast<float>(cos(toRadians(180.0f - i * 180.0f / (float)precision)));
			float tmp = toRadians(j * 360 / (float)precision);
			float x = static_cast<float>(-cos(tmp) * abs(cos(asin(y))));
			float z = static_cast<float>(sin(tmp) * abs(cos(asin(y))));
			int idx = i * (precision + 1) + j;
			mVertices[idx] = glm::vec3(x, y, z);
			mTexCoords[idx] = glm::vec2(j / (float)precision,
				i / (float)precision);
			mNormals[idx] = glm::vec3(x, y, z);
		}
	}

	for (int i = 0; i < precision; i++) {
		for (int j = 0; j < precision; j++) {
			int base = 6 * (i * precision + j);
			mIndices[base] = i * (precision + 1) + j;
			mIndices[base + 1] = i * (precision + 1) + j + 1;
			mIndices[base + 2] = (i + 1) * (precision + 1) + j;
			mIndices[base + 3] = i * (precision + 1) + j + 1;
			mIndices[base + 4] = (i + 1) * (precision + 1) + j + 1;
			mIndices[base + 5] = (i + 1) * (precision + 1) + j;
		}
	}
}
