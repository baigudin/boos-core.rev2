/**
 * Main thread.
 * 
 * @author    Sergey Baigudin, baigudin@mail.ru
 * @copyright 2016 Sergey Baigudin
 * @license   http://baigudin.software/license/
 * @link      http://baigudin.software
 */
namespace core
{
  class MainThread : public Thread
  {
    
  public:

    /** 
     * Constructor.
     */
    MainThread()
    {
    }

    /** 
     * Destructor.
     */
    virtual ~MainThread()
    {
    }
    
    /**
     * Default run method.
     */  
    virtual void run()
    {
      ::Main::main(0, NULL);
    }
    
  };
}
