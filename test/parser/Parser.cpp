/**
 * TEST feed parser.
 *
 * @package     neix
 * @author      Thomas Schwarz
 * @copyright   Copyright (c) 2020, Thomas Schwarz
 * @license     -
 * @since       Version 0.1.0
 * @filesource
 */
#include <cstring>
#include <fstream>
#include <string>
#include <gtest/gtest.h>

#include "parser/FactoryParser.h"
#include "parser/Parser.h"

using namespace std;
using namespace neix;
namespace
{
    TEST(Parser, main)
    {
        ifstream atom(TEST_ASSET_REDDIT);
        stringstream atomContent;
        atomContent << atom.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(atomContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        string configName = "dateFormat";
        string configValue = "%d.%m.%Y %H:%M";
        vector<pair<string, string>> config;
        config.emplace_back(configName, configValue);
        parser->applyConfig(config);

        char *dateFormat = parser->getTimeFormatUI();
        EXPECT_TRUE(strcmp(dateFormat, "%d.%m.%Y %H:%M") == 0);

        string htmlText = "<h1>Text</h1> <p>and words</p>";
        string renderedText = parser->renderTextToPlaintext(htmlText.c_str());
        EXPECT_TRUE(strcmp(renderedText.c_str(), "Text and words") == 0);

        parser->setRenderCommand("w3m -dump -T text/html");
        renderedText = parser->renderTextToPlaintext(htmlText.c_str());
        EXPECT_TRUE(strcmp(renderedText.c_str(), "Text\n\nand words") == 0);

        struct rssItem *item = nullptr;
        while ((item = parser->getFeedItem()) != nullptr)
        {
            EXPECT_NE(item, nullptr);
        }
    }

    TEST(Parser, atom)
    {
        ifstream atom(TEST_ASSET_ATOM);
        stringstream atomContent;
        atomContent << atom.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(atomContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);

        string title = parser->getFeedTitle();
        EXPECT_EQ(title, "Atom-Powered Robots Run Amok");

        string content = parser->getFeedContent();
        EXPECT_EQ(content, "Some text.");

        string link = parser->getFeedLink();
        EXPECT_EQ(link, "http://example.org/2003/12/13/atom03");

        string date = parser->getFeedDate();
        EXPECT_EQ(date, "13.12.2003 18:30");

        char htmlText[] = "<p>Some text</p>";
        string plaintext = parser->convertHtmlToPlaintext(htmlText);
        EXPECT_EQ(plaintext, "Some text");

        string timeString = parser->formatTimeString("2020-04-26T15:15:00+02:00");
        EXPECT_EQ(timeString, "26.04.2020 15:15");

        parser->setTimeFormatUI("%d.%m.%Y");
        timeString = parser->formatTimeString("2020-04-26T12:25:00.350+02:00");
        EXPECT_EQ(timeString, "26.04.2020");
    }

    TEST(Parser, rss0x91)
    {
        ifstream rss(TEST_ASSET_RSS091);
        stringstream rssContent;
        rssContent << rss.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(rssContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }

    TEST(Parser, rss0x92)
    {
        ifstream rss(TEST_ASSET_RSS092);
        stringstream rssContent;
        rssContent << rss.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(rssContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }

    TEST(Parser, rss2x0)
    {
        ifstream rss(TEST_ASSET_RSS2);
        stringstream rssContent;
        rssContent << rss.rdbuf();

        struct rawRss rawFeed = {};
        rawFeed.content = strdup(rssContent.str().c_str());
        rawFeed.size = 1234;

        Parser *parser = FactoryParser::getInstance(rawFeed);
        parser->setTimeFormatUI("%d.%m.%Y %H:%M");

        struct rssItem *item = parser->getFeedItem();
        EXPECT_NE(item, nullptr);
    }
}
