#pragma once
#include <windows.h>
#include <gl/GL.h>
#include <stdio.h>
#pragma comment(lib,"OpenGL32.lib")
#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

namespace rgb
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 0, 255, 0 };
	const GLubyte gray[3] = { 55, 55, 55 };
	const GLubyte lightgray[3] = { 192, 192, 192 };
	const GLubyte black[3] = { 0, 0, 0 };
}

namespace Font {

	struct vec3 { float x, y, z; };

	HDC hdc;
	GLuint base;
	bool bBuilt;

	void Build(int height)
	{
		hdc = wglGetCurrentDC();
		base = glGenLists(96);
		HFONT hFont = CreateFontA(-(height), 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas");
		HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
		wglUseFontBitmaps(hdc, 32, 96, base);
		SelectObject(hdc, hOldFont);
		DeleteObject(hFont);

		bBuilt = true;
	}

	void Print(float x, float y, const unsigned char color[4], const char* format, char* text)
	{
		glColor4ub(color[0], color[1], color[2], color[3]);
		glRasterPos2f(x, y);

		va_list	args;

		va_start(args, format);
		vsprintf_s(text, strlen(text), format, args);
		va_end(args);

		glPushAttrib(GL_LIST_BIT);
		glListBase(base - 32);
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
		glPopAttrib();
	}

	vec3 centerText(float x, float y, float width, float height, float textWidth, float textHeight)
	{
		vec3 text;
		text.x = x + (width - textWidth) / 2;
		text.y = y + textHeight;
		return text;
	}

	float centerText(float x, float width, float textWidth)
	{
		if (width > textWidth)
		{
			float difference = width - textWidth;
			return (x + (difference / 2));
		}
		else
		{
			float difference = textWidth - width;
			return (x - (difference / 2));
		}
	}
}

void SetupOrtho()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void RestoreGL()
{
	glEnable(GL_DEPTH_TEST);
}

void DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y + height + 0.5f);
	glVertex2f(x - 0.5f, y - 0.5f);
	glEnd();
}
void DrawLine(float x, float y, float x2, float y2, float lineWidth, const GLubyte color[3]) {
	glLineWidth(lineWidth);
	glBegin(GL_LINE_STRIP);
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x2 - 0.5f, y2 - 0.5f);
	glEnd();
}
void DrawCircle(float cx, float cy, float r, int num_segments,const GLubyte color[3]) {
	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++) {
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		glVertex2f(x + cx, y + cy);
	}
	glEnd();
}
#endif