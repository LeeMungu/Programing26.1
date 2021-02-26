#pragma once
/*
FMOD ���̺��!!!!!
System : FMOD���õ� ��ġ���� �����ϰų�, ���带 ����ϴ� ��, �������� �ý��� ó���� ���� ���
Sound : ���� ����
Channel : ���� ������ִ� �༮
*/

#define MaxChannelBuffer 50	//�ִ� ä�� ��

class SoundPlayer final
{
	Singleton(SoundPlayer)
private:
	struct ChannelInfo
	{
		wstring SoundName;
		FMOD::Channel* Channel;
	};
	typedef map<wstring, FMOD::Sound*>::iterator SoundIter;
private:
	map<wstring, FMOD::Sound*> mSoundList;
	vector<ChannelInfo> mActiveChannels;		//���� Ȱ��ȭ �Ǿ� �ִ� ä��
	FMOD::System* mSystem;

	float mBGMVolum;
	float mEffectVolum;

private:
	SoundPlayer();
	~SoundPlayer();
public:
	void Update();
	void LoadFromFile(const wstring& keyName, const wstring& fileName, bool isLoop);
	void Play(const wstring& keyName, float volume);
	void Pause(const wstring& keyName);
	void Stop(const wstring& keyName);

	void SetBgmVolum(float vol) { mBGMVolum += vol; }
	float GetBgmvolum() { return mBGMVolum; }
	void SetBgmVolumeUpdate(const wstring& keyName, float volume);

	void SetEffectVolum(float vol) { mEffectVolum += vol; }
	float GetEffectVolum() { return mEffectVolum; }
	void SeteffVolumeUpdate(const wstring& keyName, float volume);

	//����~ MP3�÷��̾� ��������
	//void SetVolume(const wstring& keyName, float volume);
	//float GetVolume(const wstring& keyName);  
	//void SetPosition(const wstring& keyName, float time);
	//float GetPosition(const wstring& keyName);
};

