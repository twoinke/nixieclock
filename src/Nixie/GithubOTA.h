#ifndef GITHUBOTA_H
#define GITHUBOTA_H

#define UPDATE_BINFILE "Nixie.ino.bin"
#define UPDATE_BINFILE_COMPRESSED "Nixie.ino.bin.gz"
#define CONFIGFILE                   "/config.bin"


class GithubOTA
{
public:
  String release_tag;
  
  GithubOTA(String, String);
  bool checkUpdate(String);
  bool doUpdate();



protected:
  String update_host;
  String update_url;
  String download_url;
};


#endif //GITHUBOTA_H