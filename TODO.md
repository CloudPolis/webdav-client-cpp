```C++
Client::list(std::string remote_directory)
{
  ...
  auto target_path = target_path.path();
  auto target_path_without_sep = std::string(target_path, 0, target_path.find_last_not_of("/")+1);
  auto resource_path_without_sep = std::string(resource_path, 0, resource_path.find_last_not_of("/")+1);
  if (resource_path_without_sep.compare(target_path_without_sep) == 0) continue;
}

Client::info(std::string remote_resource)
{
  ...
  auto target_path = target_path.path();
  auto target_path_without_sep = std::string(target_path, 0, target_path.find_last_not_of("/")+1);
  auto resource_path_without_sep = std::string(resource_path, 0, resource_path.find_last_not_of("/")+1);
  if (resource_path_without_sep.compare(resource_urn.path()) == 0) {
  ...
  }
}
```
