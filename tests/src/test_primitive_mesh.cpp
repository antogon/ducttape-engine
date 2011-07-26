
// ----------------------------------------------------------------------------
// This file is part of the Ducttape Project (http://ducttape-dev.org) and is
// licensed under the GNU LESSER PUBLIC LICENSE version 3. For the full license
// text, please see the LICENSE file in the root of this project or at
// http://www.gnu.org/licenses/lgpl.html
// ----------------------------------------------------------------------------

#include <OgreProcedural.h>

#include "Root.hpp"
#include "game/Game.hpp"
#include "scene/Scene.hpp"
#include "scene/Node.hpp"
#include "component/MeshComponent.hpp"
#include "component/FollowPathComponent.hpp"
#include "component/LightComponent.hpp"
#include "event/EventListener.hpp"

class Main : public dt::State {
public:
    Main() {
        mRuntime = 0;
    }

    void HandleEvent(std::shared_ptr<dt::Event> e) {
        if(e->GetType() == "DT_BEGINFRAMEEVENT") {
            mRuntime += std::dynamic_pointer_cast<dt::BeginFrameEvent>(e)->GetFrameTime();
            if(mRuntime > 5.0) {
                dt::StateManager::Get()->Pop(1);
            }
        }
    }

    void OnInitialize() {
        dt::Scene* scene = AddScene(new dt::Scene("testscene"));

        OgreProcedural::Root::getInstance()->sceneManager = scene->GetSceneManager();

	dt::ResourceManager::Get()->AddResourceLocation("","FileSystem");
        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// Test primitive generation
	OgreProcedural::PlaneGenerator().setNumSegX(20).setNumSegY(20).setSizeX(150).setSizeY(150).setUTile(5.0).setVTile(5.0).realizeMesh("planeMesh");
	putMeshNoShadow("planeMesh");

	OgreProcedural::SphereGenerator().setRadius(2.f).setUTile(5.).setVTile(5.).realizeMesh("sphereMesh");
	putMeshShadow("sphereMesh", Ogre::Vector3(0,10,0));

	OgreProcedural::CylinderGenerator().setHeight(3.f).setRadius(1.f).setUTile(3.).realizeMesh("cylinderMesh");
	putMeshShadow("cylinderMesh", Ogre::Vector3(10,10,0));

	OgreProcedural::TorusGenerator().setRadius(3.f).setSectionRadius(1.f).setUTile(10.).setVTile(5.).realizeMesh("torusMesh");
	putMeshShadow("torusMesh", Ogre::Vector3(-10,10,0));

	OgreProcedural::ConeGenerator().setRadius(2.f).setHeight(3.f).setNumSegBase(36).setNumSegHeight(2).setUTile(3.).realizeMesh("coneMesh");
	putMeshShadow("coneMesh", Ogre::Vector3(0,10,-10));

	OgreProcedural::TubeGenerator().setHeight(3.f).setUTile(3.).realizeMesh("tubeMesh");
	putMeshShadow("tubeMesh", Ogre::Vector3(-10,10,-10));

	OgreProcedural::BoxGenerator().setSizeX(2.0).setSizeY(4.f).setSizeZ(6.f).realizeMesh("boxMesh");
	putMeshShadow("boxMesh", Ogre::Vector3(10,10,-10));

	OgreProcedural::CapsuleGenerator().setHeight(2.f).realizeMesh("capsuleMesh");
	putMeshShadow("capsuleMesh", Ogre::Vector3(0,10,10));

	OgreProcedural::TorusKnotGenerator().setRadius(2.f).setSectionRadius(.5f).setUTile(3.f).setNumSegCircle(64).setNumSegSection(16).realizeMesh("torusKnotMesh");
	putMeshShadow("torusKnotMesh", Ogre::Vector3(-10,10,10));

	OgreProcedural::IcoSphereGenerator().setRadius(2.).setNumIterations(3).setUTile(5.).setVTile(5.).realizeMesh("icoSphereMesh");
	putMeshShadow("icoSphereMesh", Ogre::Vector3(10,10,10));

	OgreProcedural::RoundedBoxGenerator().setSizeX(1.f).setSizeY(5.f).setSizeZ(5.f).setChamferSize(1.f).realizeMesh("roundedBoxMesh");
	putMeshShadow("roundedBoxMesh", Ogre::Vector3(20,10,10));		

        dt::Node* camnode = scene->AddChildNode(new dt::Node("camnode"));
        camnode->AddComponent(new dt::CameraComponent("cam"));
        camnode->SetPosition(Ogre::Vector3(0, 10, 10));
        camnode->FindComponent<dt::CameraComponent>("cam")->LookAt(Ogre::Vector3(0, 0, 0));

        dt::Node* planenode = scene->AddChildNode(new dt::Node("planenode"));
        planenode->AddComponent(new dt::MeshComponent("planeMesh"));

        dt::Node* spherenode = scene->AddChildNode(new dt::Node("spherenode"));
        spherenode->AddComponent(new dt::MeshComponent("sphereMesh"));

        dt::Node* cylindernode = scene->AddChildNode(new dt::Node("cylindernode"));
        cylindernode->AddComponent(new dt::MeshComponent("cylinderMesh"));

        dt::Node* torusnode = scene->AddChildNode(new dt::Node("torusnode"));
        torusnode->AddComponent(new dt::MeshComponent("torusMesh"));

        dt::Node* conenode = scene->AddChildNode(new dt::Node("conenode"));
        conenode->AddComponent(new dt::MeshComponent("coneMesh"));

        dt::Node* tubenode = scene->AddChildNode(new dt::Node("tubenode"));
        tubenode->AddComponent(new dt::MeshComponent("tubeMesh"));

        dt::Node* boxnode = scene->AddChildNode(new dt::Node("boxnode"));
        boxnode->AddComponent(new dt::MeshComponent("boxMesh"));

        dt::Node* capsulenode = scene->AddChildNode(new dt::Node("capsulenode"));
        capsulenode->AddComponent(new dt::MeshComponent("capsuleMesh"));

        dt::Node* torusknotnode = scene->AddChildNode(new dt::Node("torusknotnode"));
        torusknotnode->AddComponent(new dt::MeshComponent("torusKnotMesh"));

        dt::Node* icospherenode = scene->AddChildNode(new dt::Node("icospherenode"));
        icospherenode->AddComponent(new dt::MeshComponent("icoSphereMesh"));

        dt::Node* roundedboxnode = scene->AddChildNode(new dt::Node("roundedboxnode"));
        roundedboxnode->AddComponent(new dt::MeshComponent("roundedBoxMesh"));

        dt::Node* lightnode1 = scene->AddChildNode(new dt::Node("lightnode1"));
        lightnode1->AddComponent(new dt::LightComponent("light1"));
        lightnode1->SetPosition(Ogre::Vector3(0, 30, 0));

        dt::Node* lightnode2 = scene->AddChildNode(new dt::Node("lightnode2"));
        lightnode2->AddComponent(new dt::LightComponent("light2"));
        lightnode2->SetPosition(Ogre::Vector3(0, -10, 0));
    }

private:
    double mRuntime;
    void putMeshShadow(const std::string& meshName, const Ogre::Vector3& position)
    {
	Ogre::Entity* ent2 = OgreProcedural::Root::getInstance()->sceneManager->createEntity(meshName);
	std::cout << "created Entity " << meshName << " successfully" << std::endl;
	Ogre::SceneNode* sn = OgreProcedural::Root::getInstance()->sceneManager->getRootSceneNode()->createChildSceneNode();
	std::cout << "created ChildSceneNode for  " << meshName << " successfully" << std::endl;
	sn->attachObject(ent2);
	std::cout << "attached Entity to Child Scene Node" << std::endl;
	sn->setPosition(position);
	std::cout << "set Child Scene Node position successfully" << std::endl;
	ent2->setMaterialName("PrimitivesTest/Pebbles");
	std::cout << "set Entity Material Name successfully" << std::endl;
    }
    void putMeshNoShadow(const std::string& meshName, const Ogre::Vector3& position = Ogre::Vector3::ZERO)
    {
	Ogre::Entity* ent2 = OgreProcedural::Root::getInstance()->sceneManager->createEntity(meshName);
	Ogre::SceneNode* sn = OgreProcedural::Root::getInstance()->sceneManager->getRootSceneNode()->createChildSceneNode();
	sn->attachObject(ent2);
	sn->setPosition(position);
	ent2->setMaterialName("PrimitivesTest/RedBrick");
	ent2->setCastShadows(false);
    }
};

int main(int argc, char** argv) {
    dt::Game game;
    game.Run(new Main(), argc, argv);
    return 0;
}