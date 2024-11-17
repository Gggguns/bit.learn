#pragma once
#include "util.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <map>
#include <curl/curl.h>
using json = nlohmann::json;
// ����ʱ��ʹ��-lcurl����libcurl�⣬���磺g++ test.cpp -o test -lcurl

// �˴���д���ڿ���̨-Ӧ�ù���-����Ӧ�ú��ȡ��AK
std::string ak = "0AFgwYGcQKt4UUcwxtPqu1YjBfD7gbda";

namespace ns_path
{
    class Path
    {
    public:
        // @brief curl����http������õĻص��������ص������жԷ��ص�json��ʽ��body�����˽������������������result��
        // @param ���������libcurl���ĵ�
        // @return ����ֵ�����libcurl���ĵ�
        static size_t callback(void* ptr, size_t size, size_t nmemb, void* stream) {
            // ��ȡ����http body�����ptr�У��Ƚ���ת��Ϊstring��ʽ
            std::string s((char*)ptr, size * nmemb);
            std::string* result = static_cast<std::string*>(stream);
            *result += s;
            return size * nmemb;
        }

        //��ַת��γ��
        static void addressTranslationLatitudeAndLongitude() {
            // �ӿڵ�ַ
            std::string uri = "/geocoding/v3";

            // �����ַ
            // libcurlĬ���ǲ�֧��SSL��, �����Ҫ֧��https������libcurl�ı���ѡ��������
            std::string host = "http://api.map.baidu.com";

            // �����������
            std::map<std::string, std::string> params;
            params["address"] = "�����к������ϵ�ʮ��10��";
            params["output"] = "json";
            params["ak"] = ak;
            params["callback"] = "showLocation";

            std::string curl_result;
            //��������
            sendRequest(uri, params, &curl_result);
            std::cout << curl_result << std::endl;
            //�ü��ַ���
            size_t start = curl_result.find('(');
            size_t end = curl_result.find(')');
            std::string json_str = curl_result.substr(start + 1, end - start - 1);
            //����JSON�ַ���
            json j = json::parse(json_str);

            //��γ��
            double lng = j["result"]["location"]["lng"];
            double lat = j["result"]["location"]["lat"];
            std::cout << "lng: " << lng << std::endl;
            std::cout << "lat: " << lat << std::endl;

        }
        //��ȡָ��
        static void getGuidance(std::string* curl_result) {
            //�ӿڵ�ַ
            std::string uri = "/directionlite/v1/walking";
            // �����������
            std::map<std::string, std::string> params;
            params["origin"] = "40.01116,116.339303";
            params["destination"] = "39.936404,116.452562";
            params["output"] = "json";
            params["ak"] = ak;
            //��������
            sendRequest(uri, params, curl_result);
        }
        //��API��������
        static void sendRequest(const std::string& uri, const std::map<std::string, std::string>& params, std::string* curl_result)
        {

            // �����ַ
            // libcurlĬ���ǲ�֧��SSL��, �����Ҫ֧��https������libcurl�ı���ѡ��������
            std::string host = "http://api.map.baidu.com";

            std::string query_str = "";
            for (auto& i : params) {
                query_str += "&" + i.first + "=" + i.second;
            }
            query_str = uri + "?" + query_str.substr(1);

            // ��������
            CURL* curl;
            CURLcode result_code;
            int error_code = 0;
            curl = curl_easy_init();
            if (curl) {
                //std::string curl_result;
                std::string url = host + query_str;

                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
                curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, curl_result);
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
                result_code = curl_easy_perform(curl);
                if (result_code != CURLE_OK) {
                    std::cout << "curl_easy_perform() failed: " << curl_easy_strerror(result_code) << std::endl;
                    //����
                    return;
                }
                curl_easy_cleanup(curl);
            }
        }

        //��Json�����ָ����Ϣ
        static void extractInstrctionFromJson(const std::string& json_str)
        {
            // �� JSON �ַ�������Ϊ json ����
            json data = json::parse(json_str);

            // ��� "routes" �Ƿ����
            if (data.contains("result") && data["result"].contains("routes")) {
                // ���� routes �е�ÿ��Ԫ��
                for (const auto& route : data["result"]["routes"]) {
                    if (route.contains("steps")) {
                        // ���� steps �е�ÿ��Ԫ��
                        for (const auto& step : route["steps"]) {
                            // ����Ƿ���� instruction �ֶ�
                            if (step.contains("instruction")) {
                                // ��� instruction ��Ϣ
                                //std::cout << "Instruction: " << step["instruction"] << std::endl;
                                std::string instruction = step["instruction"];
                                ns_util::JsonUtil::removeLabel(instruction);
                                std::cout << instruction << std::endl;
                            }
                        }
                    }
                }
            }
            else {
                std::cout << "No routes or steps found in the JSON data." << std::endl;
            }
        }
    };
}