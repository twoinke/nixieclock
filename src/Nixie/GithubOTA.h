#ifndef GITHUBOTA_H
#define GITHUBOTA_H

#define CONFIGFILE                   "/config.bin"


class GithubOTA
{
public:
  const char * release_tag;

  GithubOTA(const char * , const char * , const char * , const char * );
  bool checkUpdate(const char *);
  bool doUpdate();



protected:
  const char * update_type;
  const char * update_filename;
  const char * update_host;
  const char * update_url;
  const char * download_url;
};


#endif //GITHUBOTA_H