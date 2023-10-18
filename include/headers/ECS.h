#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "ShaderClass.h"
//declaration of classes
class Component;
class Entity;
class Manager;
class Shader;


//standard size t
//using is to bring an specific memeber into the current scope
//size_t is the the size of objects in bytes and is therefore used as the return type by the sizeof operator
// we also ensure that we are not going to get negative values

using ComponentID = std::size_t;
using Group = std::size_t;

//get the id

inline ComponentID getNewComponentTypeID(){
  
    static ComponentID lastID=0u;
    return lastID++;
}
//template function for the id
//we want always have the same id depeding on the game object


//lets rember that only a copy of the static member is used on the whole programm
//the noexect returns true if an expression is declared to not throw any expections
//in this case check if the expression will return a no exeception when used on a template

template<typename T> inline ComponentID getComponentTypeID() noexcept{
    //generate a new id
    //we ensure that this is only created once
    
    static_assert (std::is_base_of<Component, T>::value, "");
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}


//tell if an entity has a component attach
//the max components and entity can have
//constexpr is constat expression, this indicates that the value is constant and is good to use on templates and arrays
constexpr std::size_t maxComponents = 32;
// and then we create an array of the components
constexpr std::size_t maxGroups = 32;
//bitset is to deal the data at the bit level
//the bit stores multiple boolean values and take lesser memory space
using ComponentBitSet = std::bitset<maxComponents>;
// we are using these array container, for fixed size arrays 
//here is the type of values is a pointer of component and the max size is the maxComponents
using ComponentArray = std::array<Component*, maxComponents>;
//the same for the group of entities
using GroupBitset = std::bitset<maxGroups>;


//class component 
class Component
{
   
public:
    //pointer to its owner
    Entity* entity;
    //virtual to overwrite it
    virtual void init(){}
    virtual void update(float deltaTime){}
    // Define a variadic template for the draw function
    virtual void draw(Shader& shader){}
   
    //virtual deconstructor
    virtual ~Component(){}

};


class Entity{

    public:
        
        
        
        Entity(Manager& mManager) : manager(mManager) {}
        //it will call the update and draw methods on all the components
        virtual void update(float deltaTime){
            //update all the comonents on the entity
            for(auto& c : components)c->update(deltaTime);
        
        }
        virtual void draw(Shader& shader){
            for(auto& c : components)c->draw(shader);
        }
        
        //check if is active 
        bool isActive()const{return active;}
        //remove entity
        void destroy(){active = false;}

        //check if it has a group
        bool hasGroup(Group mGroup)
        {
            return groupBitset[mGroup];
        }

        //for adding enityty groups and deleting, the add group is on the implementation file
        void addGroup(Group mGroup);
        void delGroup(Group mGroup)
        {
            groupBitset[mGroup] = false;
        }
        
        
        //check if it has component
        //by making it const we make sure that the method should not make changes
        template <typename T> bool hasComponent()const{
        
        //this will return true or false
            return componentBitSet[getComponentTypeID<T>()];
            //check if the component exists
        }
        //any argument can pass it
        //this means that it can have any number of arguments
        template <typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs){
            //forward is to cast and avoid duplicates
            T* c(new T(std::forward<TArgs>(mArgs)...));
            c->entity = this;
            //is a smart pointer that manges anohter object
            std::unique_ptr<Component> uPtr{c};
            //appends a new element to the end of the vector container
            //with move we ensure that the object may moveed from allowing efficient transfer of resources, it moves ownership
            components.emplace_back(std::move(uPtr));
            // we add component to the bitest and array
            componentArray[getComponentTypeID<T>()] = c;
            componentBitSet[getComponentTypeID<T>()] = true;

            //we then initialize the components
            c->init();
            return *c;

        }
        //we get the component
        template<typename T> T& getComponent() const{
        
            auto ptr(componentArray[getComponentTypeID<T>()]);
            //we cast to these data type to be converted to another data type
            return *static_cast<T*>(ptr);
        }



    private:
        
        Manager& manager;
        //keep track if the entity is active
        bool active = true;
        //all the components that is holding
        std::vector<std::unique_ptr<Component>> components;

        ComponentArray componentArray;
        ComponentBitSet componentBitSet;
        GroupBitset groupBitset;

};


//keep a list of all the entitie
class Manager{
    public:
        void update(float deltaTime){

            for(auto& e : entities)e->update(deltaTime);
        }
        void draw(Shader& shader){
        
            for(auto& e : entities)e->draw(shader);
            
        }

        void refresh(){
        
        
            //remove groups entities
            for (auto i(0u); i < maxGroups; i++)
            {
                auto& v(groupedEntities[i]);
                v.erase(
                    std::remove_if(std::begin(v), std::end(v),
                        [i](Entity* mEntity)
                {
                    return !mEntity->isActive() || !mEntity->hasGroup(i);
                }),
                    std::end(v));
            }
        
        
        
        //this removes from the vector
        //the remove if it will remove if it satisfy the parameters
            entities.erase(std::remove_if(std::begin(entities), std::end(entities),
            [](const std::unique_ptr<Entity> &mEntity)
            {
                return !mEntity->isActive();
            }),
            std::end(entities));
        }

        //add group
        void AddToGroup(Entity* mEntity, Group mGroup)
        {
            groupedEntities[mGroup].emplace_back(mEntity);
        }

        std::vector<Entity*>& getGroup(Group mGroup)
        {
            return groupedEntities[mGroup];
        }

        //also be able to add entities with classes
        Entity& addEntity(){
            Entity* e = new Entity(*this);
            std::unique_ptr<Entity> uPtr{e};
            entities.emplace_back(std::move(uPtr));
            return *e;
        }

        template <typename T, typename... TArgs>
        Entity& addEntityClass(TArgs&&... mArgs) {
            Entity* e = new T(*this, std::forward<TArgs>(mArgs)...);
            std::unique_ptr<Entity> uPtr{ e };
            entities.emplace_back(std::move(uPtr));
            return *e;
        }

    private:
        std::vector<std::unique_ptr<Entity>> entities;
        std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};


