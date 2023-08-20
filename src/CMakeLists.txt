set(udp udp/${platform}/UdpConnectionManager.cpp
        udp/${platform}/UdpConnectionManager.h)

source_group("src\\udp" FILES ${udp})

set(api
        api/ReceiverSubscriber.h
        api/ReceiverSubject.h)

source_group("src\\api" FILES ${api})

set(src
        main.cpp
        ${platform}/Networking.h
        ${platform}/Networking.cpp)

source_group("src" FILES ${udp})

set(all_src ${udp}
            ${src}
            ${api})


add_executable(${CMAKE_PROJECT_NAME} ${all_src})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        udp/${platform}
        ${platform}
        api)