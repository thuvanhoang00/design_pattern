#include <iostream>
#include <string>
#include <map>
class ICarObject{
public:
	virtual ~ICarObject() = default;
	virtual void Run() = 0;
};

class VF3 : public ICarObject
{
public:
	VF3(){std::cout << "Created VF3\n";}
	~VF3(){}
	// this is very important function
	static ICarObject* Create(){
		return new VF3();
	}	
	void Run() override{}
};


/*
 * This class follow the open-closed principle
 */
class ExtCarFactory{
	typedef ICarObject *(*CreateCarObjectCallback)();
public:
	static void RegisterObject(std::string type, CreateCarObjectCallback cb){
		s_objects[type] = cb;
	}
	static void UnregisterObject(std::string type){
		s_objects.erase(type);
	}

	// classic factory function
	static ICarObject* CreateCar(std::string type){
		CallbackMap::iterator it = s_objects.find(type);
		if(it != s_objects.end()){
			return (it->second)();
		}
		return nullptr;
	}

private:
	typedef std::map<std::string, CreateCarObjectCallback> CallbackMap;
	static CallbackMap s_objects;
};

// initialize static obj
ExtCarFactory::CallbackMap ExtCarFactory::s_objects;



// add more car type in future...
class VF99 : public ICarObject
{
public:
	VF99(){std::cout << "Created VF99\n";}
	~VF99(){}
	void Run() override{}
	static ICarObject* Create(){
		return new VF99();
	}
private:
	
};
int main()
{
	ExtCarFactory::RegisterObject("VF3", VF3::Create);
	ExtCarFactory::RegisterObject("VF99", VF99::Create);
	std::string input;
	std::cin >> input;
	ICarObject* object = ExtCarFactory::CreateCar(input);

	if(!object) delete object;

	ICarObject* obj2 = ExtCarFactory::CreateCar("VF99");
	
	if(obj2) delete obj2;

	return 0;
}
