project(galaxyminers)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( galaxyminers galaxyminers galaxyminers.cpp )
target_include_directories( galaxyminers PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( galaxyminers ${CMAKE_SOURCE_DIR}/../ricardian )