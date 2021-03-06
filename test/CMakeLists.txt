# Assets for testing
set(TestAssetsPath "${PROJECT_SOURCE_DIR}/test/assets")
add_compile_definitions(MAIN_CONFIG_PATH_TEST="${TestAssetsPath}/testNeix.conf")
add_compile_definitions(FEED_CONFIG_PATH_TEST="${TestAssetsPath}/testFeeds.conf")
add_compile_definitions(IMPORT_CONFIG_PATH_TEST="${TestAssetsPath}/importFeeds.conf")
add_compile_definitions(TEST_ASSET_ATOM="${TestAssetsPath}/atom.xml")
add_compile_definitions(TEST_ASSET_REDDIT="${TestAssetsPath}/reddit.xml")
add_compile_definitions(TEST_ASSET_RSS091="${TestAssetsPath}/rss0.91.xml")
add_compile_definitions(TEST_ASSET_RSS092="${TestAssetsPath}/rss0.92.xml")
add_compile_definitions(TEST_ASSET_RSS2="${TestAssetsPath}/rss2.0.xml")
add_compile_definitions(TEST_ASSET_OPML="${TestAssetsPath}/opml.xml")

FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)
FILE(GLOB parser ${PROJECT_SOURCE_DIR}/src/parser/*.cpp)
FILE(GLOB config ${PROJECT_SOURCE_DIR}/src/config/*.cpp)
FILE(GLOB helper ${PROJECT_SOURCE_DIR}/src/helper/*.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)
FILE(GLOB testApplication ${PROJECT_SOURCE_DIR}/test/application/*.cpp)
FILE(GLOB testParser ${PROJECT_SOURCE_DIR}/test/parser/*.cpp)
FILE(GLOB testFeeds ${PROJECT_SOURCE_DIR}/test/feed/*.cpp)
FILE(GLOB testConfig ${PROJECT_SOURCE_DIR}/test/config/*.cpp)
FILE(GLOB testHelper ${PROJECT_SOURCE_DIR}/test/helper/*.cpp)

add_executable(tests
    ${src}
    ${tests}

    ${testConfig}
    ${testHelper}
    ${testFeedLoader}
    ${testFeeds}
    ${testParser}
    ${testApplication}
)
target_link_libraries(tests gtest)
target_link_libraries(tests neixApplication ${CURSES_LIBRARIES})
target_link_libraries(tests neixFeed ${CURL_LIBRARY})
target_link_libraries(tests neixParser)
target_link_libraries(tests neixConfig)
target_link_libraries(tests neixHelper)
