#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <ESP8266httpUpdate.h>


#include "GithubOTA.h"


GithubOTA::GithubOTA(const char *  host, const char *  url, const char *  type, const char *  filename)
{
  update_host     = host;
  update_url      = url;
  update_type     = type;
  update_filename = update_filename;
}


bool GithubOTA::checkUpdate(const char * current_release_tag)
{
  JsonDocument doc;
  WiFiClientSecure client;

  client.setInsecure();

  if (!client.connect(update_host, 443)) 
  {
    Serial.printf("Connection to %s failed\n", update_host );
    return false;
  }

  Serial.printf("Connection to %s established\n", update_host);

  char request[255];
  snprintf(request, 255, "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: NixieClock_ESP_OTA_GitHubUpdater\r\nConnection: close\r\n\r\n", update_url, update_host);

  client.print(request);

  
  while (client.connected()) 
  {
    String response = client.readStringUntil('\n');
    if (response == "\r") 
    {
			break;
    }
  }

  String response = client.readStringUntil('\n');

  DeserializationError error = deserializeJson(doc, response);

  if (error)
  {
    Serial.println("Error parsing JSON response");
    return false;
  }

  if (! doc.containsKey("tag_name")) 
  {
    Serial.println("no release tag found");
    return false;
  }

  release_tag = doc["tag_name"];

  Serial.printf("Found release %s\n", release_tag);
  Serial.printf("Current release %s\n", current_release_tag); 

  if (strcmp(release_tag, current_release_tag) == 0 || doc["prerelease"]) 
  {
    Serial.println("No update found.");
    return false;
  }

  Serial.println("Update found.");

  JsonArray assets = doc["assets"];
  bool valid_asset = false;
  for (auto asset : assets) 
  {
    const char* asset_type = asset["content_type"];
    const char* asset_name = asset["name"];
    const char* asset_url = asset["browser_download_url"];

    Serial.printf("asset found: Name: [%s], Type: [%s], URL: [%s]\n", asset_name, asset_type, asset_url);

    if (strcmp(asset_type, update_type) == 0 && strcmp(asset_name, update_filename) == 0) 
    {
      download_url = asset_url;

      Serial.printf("Update URL: %s\n", download_url);

      return true;
    }
  }

  return false;
}


bool GithubOTA::doUpdate()
{
  WiFiClientSecure updateClient;
  Serial.printf("Updating from %s\n", download_url);

  updateClient.setInsecure();



  bool mfln = updateClient.probeMaxFragmentLength("objects.githubusercontent.com", 443, 1024);
  if (mfln) 
  {
    updateClient.setBufferSizes(1024, 1024);
    Serial.println("Set buffer sizes to 1024");
  }


  ESPhttpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  t_httpUpdate_return ret = ESPhttpUpdate.update(updateClient, download_url);

  switch (ret) 
  {
    case HTTP_UPDATE_FAILED:
        Serial.println("Update Failed: " + ESPhttpUpdate.getLastErrorString());
        return false;

    case HTTP_UPDATE_NO_UPDATES:
        Serial.println("HTTP_UPDATE_NO_UPDATES");
        return false;

    case HTTP_UPDATE_OK:
        Serial.println("Update successful");
        return true;
  }

  return false;
}
