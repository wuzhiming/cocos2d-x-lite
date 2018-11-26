/****************************************************************************
Copyright (c) 2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated engine source code (the "Software"), a limited,
worldwide, royalty-free, non-assignable, revocable and non-exclusive license
to use Cocos Creator solely to develop games on your target platforms. You shall
not use Cocos Creator software for developing other software or tools that's
used for developing games. You are not granted to publish, distribute,
sublicense, and/or sell copies of Cocos Creator.

The software or tools in this License Agreement are licensed, not sold.
Xiamen Yaji Software Co., Ltd. reserves all rights not expressly granted to you.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#pragma once

#include "base/ccMacros.h"
#include "base/CCRef.h"

#include "FacebookGameSDK.h"

NS_CC_BEGIN
/**
@brief    The Facebook Games SDK wrapper.

*/
class FacebookPCGamesSDK : public Ref
{
public:
	FacebookPCGamesSDK();
	~FacebookPCGamesSDK();

	/**
	@brief  init FacebookGameSDK
	@param  Facebook Developer Account ID
	*/
	void init(std::string strAppId);

	/**
	@brief  login
	*/
	void login();

	/**
	@brief  push event to Analysis Statistics
	*/
	void pushEvent(int eventId);

private:

	unsigned long long appId;

	std::wstring accessToken;

	std::shared_ptr<facebook_games_sdk::User> loginUser;

private:

	void _prepareEvent();

	bool _isEventPrepared;
};

NS_CC_END
