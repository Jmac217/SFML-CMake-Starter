#pragma once
namespace Mac {

	template<typename Derived, typename T>
	struct ResourceManager
	{
		ResourceManager(const std::string& l_pathsFile)
		{
			LoadPaths(l_pathsFile);
		}

		virtual ~ResourceManager()
		{
			PurgeResouces();
		}

		T* GetResource(const std::string& l_id)
		{
			auto resource = Find(l_id);
			return (
					resource
					? resource->first
					: nullptr
			);
		}

		std::string GetPath(const std::string& l_id)
		{
			auto path = m_paths.find(l_id);
			return
			(
				path != m_paths.end()
				?	path->second
				:	""
			);
		}

		bool RequiresResource(const std::string& l_id)
		{
			auto resource = Find(l_id);
			if (resource)
			{
				++resource->second;
				return true;
			}

			auto path = m_paths.find(l_id);
			if (path == m_paths.end())
				return false;

			T* resourcePath = Load(path->second);
			if (!resourcePath)
				return false;

			m_resources.emplace(l_id, std::make_pair(resourcePath, 1));
			return true;
		}

		bool ReleaseResource(const std::string& l_id)
		{
			auto resource = Find(l_id);
			if (!resource)
				return false;

			--resource->second;
			if (!resource->second)
				Unload(l_id);

			return true;
		}

		void PurgeResouces()
		{
			std::cout << "Purging ALL Resources: " << std::endl;
			while (m_resources.begin() != m_resources.end())
			{
				std::cout << "Removing: " << m_resources.begin()->first << std::endl;
				delete m_resources.begin()->second.first;
				m_resources.erase(m_resources.begin());
			}
			std::cout << "Purging finished." << std::endl;
		}

	protected:
		T* Load(const std::string& l_path)
		{
			return static_cast<Derived*>(this)->Load(l_path);
		}
	private:
		std::pair<T*, unsigned int>* Find(const std::string& l_id) {
			auto itr = m_resources.find(l_id);
			return (itr != m_resources.end() ? &itr->second : nullptr);
		}

		bool Unload(const std::string& l_id)
		{
			auto i = m_resources.find(l_id);
			if (i == m_resources.end())
				return false;

			delete i->second.first;

			m_resources.erase(i);

			return true;
		}

		void LoadPaths(const std::string& l_pathFile) {
			std::ifstream paths;
			paths.open(Utils::GetWorkingDirectory() + l_pathFile);
			if (paths.is_open()) {
				std::string line;
				while (std::getline(paths, line)) {
					std::stringstream keystream(line);
					std::string pathName;
					std::string path;
					keystream >> pathName;
					keystream >> path;
					m_paths.emplace(pathName, path);
				}
				paths.close();
				return;
			}
			std::cerr <<
				"! Failed loading the path file: "
				<< l_pathFile << std::endl;
		}

		std::unordered_map<std::string, std::pair<T*, unsigned>> m_resources;
		std::unordered_map<std::string, std::string> m_paths;
	};
}