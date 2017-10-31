/***************************************************************************
 * Copyright (C) 2011
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#ifndef GUI_SCROLLBAR_HPP_
#define GUI_SCROLLBAR_HPP_

#include "gui/GuiElement.h"
#include "gui/GuiButton.h"

class GuiScrollbar : public GuiElement, public sigslot::has_slots<>
{
	public:
		GuiScrollbar(s32 height);
		virtual ~GuiScrollbar();
		void ScrollOneUp();
		void ScrollOneDown();
		s32 GetSelectedItem() { return SelItem; }
		s32 GetSelectedIndex() { return SelInd; }
		void draw(CVideo * video);
		void update(GuiController * t);

		//! Signals
		sigslot::signal2<s32, s32> listChanged;
		//! Slots
		void SetScrollSpeed(s32 speed){ScrollSpeed = speed;};
		void SetPageSize(s32 size);
		void SetRowSize(s32 size);
		void SetSelectedItem(s32 pos);
		void SetSelectedIndex(s32 pos);
		void SetEntrieCount(s32 cnt);

		void setSoundClick(GuiSound * snd){
		    clickSound = snd;
		    arrowUpBtn->setSoundClick(snd);
		    arrowDownBtn->setSoundClick(snd);
		}

        void setImageScrollbarLine(GuiImage * img){
            if(img){
                scrollbarLineImage = img;
                scrollbarLineImage->setParent(this);
                scrollbarLineImage->setParent(this);
                scrollbarLineImage->setAlignment(ALIGN_CENTER | ALIGN_MIDDLE);
                scrollbarLineImage->setPosition(0, 0);
            }
        }

        void setImageArrowDown(GuiImage * img){
            if(img){
                arrowDownImage = img;
                arrowDownBtn->setSize(img->getWidth(), img->getHeight());
                arrowDownBtn->setImage(img);
            }
        }

        void setImageArrowUp(GuiImage * img){
            if(img){
                arrowUpImage = img;
                arrowUpBtn->setSize(img->getWidth(), img->getHeight());
                arrowUpBtn->setImage(img);
            }
        }

        void setImageScrollbarBox(GuiImage * img){
            if(img){
                scrollbarBoxImage = img;
                scrollbarBoxBtn->setSize(img->getWidth(), height);
                scrollbarBoxBtn->setImage(img);

                width = img->getWidth();

                MaxHeight = height * 0.5f - (img ? (img->getHeight() * 0.5f) : 0) - (arrowUpImage ? arrowUpImage->getHeight() : 0);
                MinHeight = -height * 0.5f + (img ? (img->getHeight() * 0.5f) : 0) + (arrowDownImage ? arrowDownImage->getHeight() : 0);
            }
        }

	protected:
		void setScrollboxPosition(s32 SelItem, s32 SelInd);
		void OnUpButtonClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger);
		void OnDownButtonClick(GuiButton *button, const GuiController *controller, GuiTrigger *trigger);
		void OnBoxButtonHold(GuiButton *button, const GuiController *controller, GuiTrigger *trigger);

		u32 ScrollState;
		u16 ScrollSpeed;

		s32 MinHeight;
		s32 MaxHeight;
		s32 SelItem;
		s32 SelInd;
		s32 PageSize;
		s32 EntrieCount;
		s32 pressedChan;

		GuiButton * arrowUpBtn;
		GuiButton * arrowDownBtn;
		GuiButton * scrollbarBoxBtn;

		GuiSound * clickSound = NULL;

		GuiImage * scrollbarLineImage = NULL;
		GuiImage * arrowDownImage = NULL;
		GuiImage * arrowUpImage = NULL;
		GuiImage * scrollbarBoxImage = NULL;

		GuiTrigger touchTrigger;
		GuiTrigger wpadTouchTrigger;
};

#endif
