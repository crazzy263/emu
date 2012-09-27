#ifndef __core_usersFactory_hpp__
#define __core_usersFactory_hpp__

#include <common/objectsFactory.hpp>
#include <common/log.hpp>
#include <user/userIdGenerator.hpp>

namespace eMU {
namespace core {
namespace user {

template<typename userImpl>
class factory_t: public objectsFactory_t<userImpl> {
public:
    factory_t(size_t maxNumOfUsers):
      idGenerator_(maxNumOfUsers) {}

    userImpl* construct() {
        int16 id = idGenerator_.get();

        if(id == invalidId_c) {
            LOG_ERROR << "Generated invalid id!" << std::endl;
            return NULL;
        }

        userImpl *user = objectsPool_.construct(id);
        return user;
    }

    void destroy(userImpl *user) {
        int16 id = user->id();
        idGenerator_.insert(id);
        objectsPool_.destroy(user);
    }

protected:
    idGenerator_t idGenerator_;
};

}
}
}

#endif