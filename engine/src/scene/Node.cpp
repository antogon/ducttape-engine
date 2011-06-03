#include "Node.hpp"

#include "utils/Logger.hpp"

#include <memory>

namespace dt {

Node::Node() {
    mName = "node-generated-name";
    mParent = nullptr;
}

Node::Node(const std::string &name) {
    mName = name;
    mParent = nullptr;
}

void Node::AddChildNode(Node* child) {
    std::string key = child->GetName();
    mChildren[key] = *child;
    mChildren[key].SetParent(this);
}

void Node::AddComponent(const std::string& name) {
    if(!HasComponent(name)) {
        mComponents.push_back(name);
    }
}

Node* Node::FindChildNode(const std::string& name, bool recursive) {
    if(mChildren.find(name)!=mChildren.end())
        return mChildren.find(name)->second;

    if(recursive){
        for(boost::ptr_map<std::string, Node>::iterator itr = mChildren.begin(); itr != mChildren.end(); itr++) {
            if(itr->first == name)
                return itr->second;
            else {
                Node* childNode = itr->second->FindChildNode(name, recursive);
                if(childNode != nullptr)
                    return childNode;
            }
        }
    }
    return nullptr;
}

bool Node::HasComponent(const std::string &name) {
    for(std::string& n: mComponents) {
        if(n == name)
            return true;
    }
    return false;
}

void Node::RemoveChildNode(const std::string& name) {
    if(FindChildNode(name, false) != nullptr) {
        mChildren.erase(name);
    }
}

void Node::RemoveComponent(const std::string& name) {
    if(HasComponent(name)) {
        for(auto iter = mComponents.begin(); iter != mComponents.end(); ++iter) {
            if(*iter == name)
                iter = mComponents.erase(iter);
        }
    }
}

const std::string& Node::GetName() const {
    return mName;
}

Ogre::Vector3 Node::GetPosition(Node::RelativeTo rel) const {
    if(rel == PARENT || mParent == nullptr) {
        return mPosition;
    } else {
        return mParent->GetPosition(ROOT) + mPosition;
    }
}

void Node::SetPosition(Ogre::Vector3 position, Node::RelativeTo rel) {
    if(rel == PARENT || mParent == nullptr) {
        mPosition = position;
    } else {
        mPosition = position - mParent->GetPosition(ROOT);
    }
}

Ogre::Vector3 Node::GetScale(Node::RelativeTo rel) const {
    if(rel == PARENT || mParent == nullptr) {
        return mScale;
    } else {
        Ogre::Vector3 p = mParent->GetScale(ROOT);
        return Ogre::Vector3(p.x * mScale.x, p.y * mScale.y, p.z * mScale.z);
    }
}

void Node::SetScale(Ogre::Vector3 scale, Node::RelativeTo rel) {
    if(rel == PARENT || mParent == nullptr) {
        mScale = scale;
    } else {
        Ogre::Vector3 p = mParent->GetScale(ROOT);
        mScale = Ogre::Vector3(scale.x / p.x, scale.y / p.y, scale.z / p.z);
    }
}

void Node::SetScale(Ogre::Real scale, Node::RelativeTo rel) {
    SetScale(Ogre::Vector3(scale, scale, scale), rel);
}

Ogre::Quaternion Node::GetRotation(Node::RelativeTo rel) const {
    if(rel == PARENT || mParent == nullptr) {
        return mRotation;
    } else {
        // Logger::Get().Error("Not implemented: Node::GetRotation relative to ROOT");
        return mParent->GetRotation(ROOT) * mRotation;
    }
}

void Node::SetRotation(Ogre::Quaternion rotation, Node::RelativeTo rel) {
    if(rel == PARENT || mParent == nullptr) {
        mRotation = rotation;
    } else {
        Logger::Get().Error("Not implemented: Node::SetRotation relative to ROOT");
        // TODO: implement backward rotation
        // Ogre::Quaternion p = mParent->GetRotation(ROOT);
        mRotation = rotation;
    }
}

void Node::SetParent(Node* parent) {
    if(parent != nullptr) {
        if(parent->FindChildNode(mName, false) == nullptr) { // we are not already a child of the new parent
            parent->AddChildNode(this);
            return;
        }
    }
    if(mParent != parent && mParent != nullptr) {
        // new parent
        mParent->RemoveChildNode(mName);
    }

    mParent = parent;
}

Node* Node::GetParent() {
    return mParent;
}

}
