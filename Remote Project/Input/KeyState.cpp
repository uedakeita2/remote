#include <DxLib.h>
#include "KeyState.h"
#include "InputState.h"
#include "../_debug/_DebugConOut.h"



KeyState::KeyState()
{
	_KeyConDef.reserve(static_cast<size_t>(end(INPUT_ID()))); // �������̍Ĕz�u������邽�߁A���炩���ߕK�v���m�ۂ���reserve���g�p����
	_KeyConDef.emplace_back(KEY_INPUT_LEFT);
	_KeyConDef.emplace_back(KEY_INPUT_RIGHT);
	_KeyConDef.emplace_back(KEY_INPUT_UP);
	_KeyConDef.emplace_back(KEY_INPUT_DOWN);
	_KeyConDef.emplace_back(KEY_INPUT_Z);
	_KeyConDef.emplace_back(KEY_INPUT_X);
	_KeyConDef.emplace_back(KEY_INPUT_A);
	_KeyConDef.emplace_back(KEY_INPUT_S);

	FILE* file;
	fopen_s(&file, "data/key.data", "rb");
	if (file == nullptr)
	{
		_KeyCon = _KeyConDef; // ���g�̺�߰
	}
	else
	{
		//_keyCon�ɂ͒l�������Ă��Ȃ�����v�f(INPUT_ID��)�̃T�C�Y���m�ۂ��Ȃ��Ƃ����Ȃ�
		_KeyCon.resize(static_cast<int>(end(INPUT_ID())));
		fread(
			_KeyCon.data(),
			sizeof(_KeyCon[0]),
			_KeyCon.size(),
			file);
		fclose(file);
	}

	modeKeyOld = 1;	// F1�̵���޷�


	func = &KeyState::RefKeyData;  // �֐��߲�����g���Ƃ���&���g���@��������ް�֐��߲�� �N���X����H�遁���O���
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf); // _buf�͂��ׂĂ����݂̉�����Ԃ��Ƃ�
	(this->*func)(); // �������g���߲�����this
}

void KeyState::RefKeyData(void)
{
	// _buf�ɓ����Ă��� inputID�̷�(enumclass)�̏���state��set���g���Ă���� _buf�@inputID���̏���set���g���ā@�͈�for�����g���@_keycon���g����set����@f1�L�[����������func�̓��e��setConFig�ɕς���@f1key���������u��refKeyData�̌Ăяo���ɂ��ǂ��@�g���[�X�Ő؂�ւ������ς�������Ƃ�\������
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_KeyCon[static_cast<int>(id)]]);	// <size_t>�ł���
	}


	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_confID = INPUT_ID::LEFT;	// �ݽ�׸��ł͈��ڂ����񂹂Ȃ� max�l�����邽�߉������Ȃ��܂ܔ�����  
		func = &KeyState::SetKeyConfig;
		TRACE("�L�[�R���t�B�O�J�n\n");
		TRACE("%d%d�Ԗڂ̃L�[�ݒ�\n", static_cast<int>(_confID));
	}
}

void KeyState::SetKeyConfig(void)
{
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::RefKeyData;
		TRACE("�L�[�R���t�B�O�I��\n");
		return;
	}

	// ��ڲ԰�̷�����0����
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	// 1�x�����������ǂ����𒲂ׂ�
	auto checkKey = [&](int id) {
		for (auto ckId = INPUT_ID::LEFT; ckId < _confID; ++ckId)
		{
			if (_KeyCon[static_cast<int>(ckId)] == id)
			{
				return false;	// �d������
			}
		}
		return true;	// �d������
	};


	// ���ύX
	for (int id = 0; id < sizeof(_buf); id++)
	{
		if (!checkKey(id))
		{
			continue;	// �R���e�B�j���[���for (int id = 0; id < sizeof(_buf); id++)
		}

		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			_KeyCon[static_cast<int>(_confID)] = id;
			++_confID; // ����++���Ă��邩�킩��Ȃ�����O���Z������
			TRACE("%d��ݒ�\n", id);

			if (_confID >= end(INPUT_ID()))
			{
				FILE* file;
				fopen_s(&file, "data/key.data", "wb");
				if (file != nullptr)
				{
					/*for (int j = 0; j < _KeyCon.size(); j++)
					{
						fwrite(
							&_KeyCon[j],
							sizeof(_KeyCon[j]),
							1,
							file
						);
					}*/ // �ް����o���o���ɂ���Ƃ��Ɏg�� 

					fwrite(
						_KeyCon.data(), // �v�f���߲������擾���Ă����n�� 
						sizeof(_KeyCon[0]),// sizeof(_KeyCon[0]) * _KeyCon.size() , 1 �ł��悢�@�ް����A���ő��݂��Ă��鎞
						_KeyCon.size(),
						file
					);
					fclose(file);
				}

				TRACE("�L�[�R���t�B�O�I��\n");
				func = &KeyState::RefKeyData;
				break;
			}


			TRACE("%d%d�Ԗڂ̃L�[�ݒ�\n",
				static_cast<int>(_confID) + 1,
				end(INPUT_ID())
			);
		}
	}
}
