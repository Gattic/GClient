// Copyright 2020 Robert Carneiro, Derek Meer, Matthew Tabak, Eric Lujan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef _RUMSGBOX
#define _RUMSGBOX

#include "../GItems/RUComponent.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

class gfxpp;
class RUButton;
class RUTextbox;
class RULabel;
class RUImageComponent;

class RUMsgBox : public RUComponent
{
protected:
	GPanel* panel;
	int type;

	static shmea::GString OK_BUTTON;
	static shmea::GString YES_BUTTON;
	static shmea::GString NO_BUTTON;
	static shmea::GString SUBMIT_BUTTON;

	static const int DEFAULT_WIDTH = 500;
	static const int DEFAULT_HEIGHT = 180;

	// message
	RULabel* lbltitle;
	RULabel* lblmsg;

	// confirm
	RUButton* msgButtonOK;

	// yes no
	RUButton* confirmButtonYES;
	RUButton* confirmButtonNO;
	int confirmButtonClicked;

	// input box
	RUTextbox* inputText;
	RUButton* inputButtonSubmit;
	shmea::GString inputSubmitText;

	// event listeners
	GeneralListener MouseDownListener;

	// events
	virtual void onMouseDown(gfxpp*, GPanel*, int, int);

public:
	static const int MESSAGEBOX = 0;
	static const int CONFIRMBOX = 1;
	static const int INPUTBOX = 2;

	// constructors & destructor
	RUMsgBox(GPanel*, int, GeneralListener = GeneralListener());
	virtual ~RUMsgBox();

	static void MsgBox(GPanel*, const char*, const char*, int, GeneralListener = GeneralListener());
	static void MsgBox(GPanel*, shmea::GString, const char*, int, GeneralListener = GeneralListener());
	static void MsgBox(GPanel*, const char*, shmea::GString, int, GeneralListener = GeneralListener());
	static void MsgBox(GPanel*, shmea::GString, shmea::GString, int, GeneralListener = GeneralListener());

	// events
	void msgButtonOKClicked(gfxpp*);
	void confirmButtonYESClicked(gfxpp*);
	void confirmButtonNOClicked(gfxpp*);
	void inputButtonSUBMITClicked(gfxpp*);

	// render
	virtual void updateBackground(gfxpp*);
	virtual shmea::GString getType() const;
};

#endif
