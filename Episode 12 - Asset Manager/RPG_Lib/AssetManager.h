#pragma once
#include "Singleton.h"
#include "IAsset.h"
#include "TypeFactory.h"
#include <map>

class AssetManager : public UnCopyable
{
	std::map<std::string, IAsset*> m_Assets;

	friend class Singleton<AssetManager>;
	AssetManager() {}

public:

	template<class T>
	bool LoadAsset(std::string assetLocation)
	{
		TheAssetTypeFactory::Pointer()->Register<T>(typeid(T).name());
		IAsset* asset = TheAssetTypeFactory::Pointer()->Create(typeid(T).name());

		bool loaded = asset->Load(assetLocation);
		if (!loaded)
			m_Assets.insert(std::pair<std::string, IAsset*>(assetLocation, asset));
		else
		{
			delete asset;
			printf("LoadAsset: Faild to load asset: %s", assetLocation.c_str());
			return true;
		}

		return false;
	}

	template<class T>
	T* GetAsset(std::string assetLocation)
	{
		auto a = m_Assets.find(assetLocation);
		if (a == m_Assets.end())
		{
			printf("GetAsset: Faild to find asset: %s", assetLocation.c_str());
			return nullptr;
		}
		else
		{
			T* tmp = dynamic_cast<T*>(a->second);
			if (tmp != nullptr)
				return tmp;
			else
			{
				printf("GetAsset: Faild to cast asset to: %s", typeid(T).name()); //had T here
				return nullptr;
			}
		}
	}
};

typedef Singleton<TypeFactory<IAsset>> TheAssetTypeFactory;
typedef Singleton<AssetManager> TheAssetManager;