#include "pch.h"
#include "UiManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Ui.h"


UiManager::UiManager()
{
    //Ui레이어 별로 벡터하나씩 맵에 집어넣는다.
    for (int i = 0; i < (int)UiLayer::End; ++i)
    {
        vector<Ui*> emptyVector;
        mUiList.insert(make_pair((UiLayer)i, emptyVector));
    }
    for (int i = 0; i < (int)ObjectLayer::End; ++i)
    {
        vector<GameObject*> emptyVector;
        mObjectList.insert(make_pair((ObjectLayer)i, emptyVector));
    }
}

void UiManager::Init()
{
    UiIter iter = mUiList.begin();
    for (; iter != mUiList.end(); ++iter)
    {
        for (int i = 0; i < iter->second.size(); ++i)
        {
            iter->second[i]->Init();
        }
    }

    //필요 없을까? 있을ㄲ?

    //ObjectIter objectIter = mObjectList.begin();
    //for (; objectIter != mObjectList.end(); ++objectIter)
    //{
    //    for (int i = 0; i < objectIter->second.size(); ++i)
    //    {
    //        objectIter->second[i]->Init();
    //    }
    //}
}

void UiManager::Release()
{
    UiIter iter = mUiList.begin();
    for (; iter != mUiList.end(); ++iter)
    {
        for (int i = 0; i < iter->second.size(); ++i)
        {
            iter->second[i]->Release();
            SafeDelete(iter->second[i]);
        }
        iter->second.clear();
        iter->second.shrink_to_fit();
    }

    ObjectIter objectIter = mObjectList.begin();
    for (; objectIter != mObjectList.end(); ++objectIter)
    {
        for (int i = 0; i < objectIter->second.size(); ++i)
        {
            objectIter->second[i]->Release();
            SafeDelete(objectIter->second[i]);
        }
        objectIter->second.clear();
        objectIter->second.shrink_to_fit();
    }
}

void UiManager::Update()
{
    //Ui리스트만 objectManager는 넘겨받고 주기용.
    if (mUiList.size() != NULL)
    {
        UiIter iter = mUiList.begin();
        for (; iter != mUiList.end(); ++iter)
        {
            for (int i = 0; i < iter->second.size(); ++i)
            {
                //DISTROY - 제거 할때 유용할수도
                if (iter->second[i]->GetIsDestroy() == true)
                {
                    iter->second[i]->Release();
                    SafeDelete(iter->second[i]);
                    iter->second.erase(iter->second.begin() + i);
                    --i;
                    continue;
                }
                //ACTIVE - Ui에선 필요 없지만 항상 true로 유지하기
                if (iter->second[i]->GetIsActive() == true)
                {
                    iter->second[i]->Update();
                }
            }
        }
    }
}

void UiManager::Render(HDC hdc)
{
    UiIter iter = mUiList.begin();
    for (; iter != mUiList.end(); ++iter)
    {
        for (int i = 0; i < iter->second.size(); ++i)
        {
            if (iter->second[i]->GetIsActive() == true)
            {
                iter->second[i]->Render(hdc);
            }
        }
    }
}

void UiManager::AddUi(UiLayer layer, Ui* object)
{
    mUiList[layer].push_back(object);
}

//void UiManager::Erase(UiLayer layer)
//{
//    if (mUiList.find(layer) == nullptr)
//    {
//        return;
//    }
//    mUiList.erase(mUiList.find(layer));
//}

Ui* UiManager::FindUi(const string& name)
{
    UiIter iter = mUiList.begin();
    for (; iter != mUiList.end(); ++iter)
    {
        for (int i = 0; i < iter->second.size(); ++i)
        {
            if (iter->second[i]->GetName() == name)
            {
                return iter->second[i];
            }
        }
    }
    return nullptr;
}

Ui* UiManager::FindUi(UiLayer layer, const string& name)
{
    UiIter iter = mUiList.find(layer);
    for (int i = 0; i < iter->second.size(); ++i)
    {
        if (iter->second[i]->GetName() == name)
        {
            return iter->second[i];
        }
    }
    return nullptr;
}

vector<class Ui*> UiManager::FindUis(const string& name)
{
    vector<Ui*> result;

    UiIter iter = mUiList.begin();
    for (; iter != mUiList.end(); ++iter)
    {
        for (int i = 0; i < iter->second.size(); ++i)
        {
            if (iter->second[i]->GetName() == name)
            {
                result.push_back(iter->second[i]);
            }
        }
    }
    return result;
}

vector<class Ui*> UiManager::FindUis(UiLayer layer, const string& name)
{
    vector<Ui*> result;
    UiIter iter = mUiList.find(layer);
    for (int i = 0; i < iter->second.size(); ++i)
    {
        if (iter->second[i]->GetName() == name)
        {
            result.push_back(iter->second[i]);
        }
    }
    return result;
}

vector<class Ui*> UiManager::GetUiList(UiLayer layer)
{
    return mUiList[layer];
}
