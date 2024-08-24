#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <ESP8266httpUpdate.h>


#include "GithubOTA.h"


GithubOTA::GithubOTA(String host, String url)
{
  update_host = host;
  update_url  = url;
}


bool GithubOTA::checkUpdate(String current_release_tag)
{
  JsonDocument doc;
  WiFiClientSecure client;

  client.setInsecure();

  if (!client.connect(update_host, 443)) 
  {
    Serial.printf("Connection to %s failed\n", update_host.c_str() );
    return false;
  }

  Serial.printf("Connection to %s established\n", update_host.c_str());
  client.print(String("GET ") + update_url + " HTTP/1.1\r\n" +
    "Host: " + String(update_host) + "\r\n" +
    "User-Agent: NixieClock_ESP_OTA_GitHubUpdater\r\n" +
    "Connection: close\r\n\r\n");

  
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

  // const char* release_tag;

  if (! doc.containsKey("tag_name")) 
  {
    Serial.println("no release tag found");
    return false;
  }

  release_tag = String(doc["tag_name"]);
  Serial.println("Found release " + release_tag + "\n");
  Serial.printf("Current release %s\n", current_release_tag); 

  if (current_release_tag == release_tag || doc["prerelease"])
  {
    Serial.println("No update found1.");
    return false;  
  }

  // if (strcmp(release_tag.c_str(), current_release_tag.c_str()) == 0 || doc["prerelease"]) 
  // {
  //   Serial.println("No update found2.");
  //   return false;
  // }

  Serial.println("Update found.");

  JsonArray assets = doc["assets"];
  bool valid_asset = false;
  for (auto asset : assets) 
  {
    const char* asset_type = asset["content_type"];
    const char* asset_name = asset["name"];
    const char* asset_url = asset["browser_download_url"];

    Serial.printf("asset found: Name: [%s], Type: [%s], URL: [%s]\n", asset_name, asset_type, asset_url);

    if (strcmp(asset_type, "application/gzip") == 0 && strcmp(asset_name, UPDATE_BINFILE_COMPRESSED) == 0) 
    {
      download_url = asset_url;

      Serial.println("Update URL:" + download_url);

      return true;
    }

    if (strcmp(asset_type, "application/octet-stream") == 0 && strcmp(asset_name, UPDATE_BINFILE) == 0) 
    {
      download_url = asset_url;

      Serial.println("Update URL:" + download_url);


      return true;
    }
  }

  return false;

}


bool GithubOTA::doUpdate()
{
  WiFiClientSecure updateClient;
  Serial.println("Updating from " + download_url);

  updateClient.setInsecure();



  bool mfln = updateClient.probeMaxFragmentLength("objects.githubusercontent.com", 443, 1024);
  if (mfln) 
  {
    updateClient.setBufferSizes(1024, 1024);
    Serial.println("Set buffer sizes to 1024");
  }

  ESPhttpUpdate.setLedPin(D8, HIGH);
  ESPhttpUpdate.rebootOnUpdate(false);
  ESPhttpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

  Serial.println("Updating from " + download_url);


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
