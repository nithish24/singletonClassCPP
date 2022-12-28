#include <iostream>
#include <mutex>

std::mutex m;

class GameSetting
{
  
  private :
  static GameSetting* _instance;
  
  int _brightness_level {0}, _volume_level{0};
  
  GameSetting() : _brightness_level{75} , _volume_level {50}
  {
      
  }
  
  GameSetting(const GameSetting& _gs) = delete;
  GameSetting& operator=(const GameSetting& _gs) = delete;
  
  public:
  static GameSetting* getInstance()
  {
      m.lock();
      if(_instance == nullptr)
      {
          _instance = new GameSetting;
      }
      m.unlock();
      return _instance;
  }
  
  void setBrightness(int value)
  {
      _brightness_level = value;
  }
  
  void setVolume(int value)
  {
      _volume_level = value;
  }
  void display_values()
  {
      std::cout << "Values are: Brightness = " << _brightness_level << " Volume = " << _volume_level << "\n";
  }
};

GameSetting* GameSetting::_instance = nullptr;

void test_function()
{
    GameSetting *GS_OBJ = GameSetting::getInstance();
    GS_OBJ->display_values();
    GS_OBJ->setBrightness(90);
    GS_OBJ->display_values();
}

int main()
{
    GameSetting *GS_OBJ = GameSetting::getInstance();
    GS_OBJ->display_values();
    GS_OBJ->setVolume(40);
    GS_OBJ->display_values();
    test_function();
    GS_OBJ->display_values();
}
