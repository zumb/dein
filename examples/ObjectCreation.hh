<?hh //partial
namespace Example;

require_once 'vendor/autoload.php';

/* Some classes with dependencies */
class FirstLevel
{
  public function __construct(
    protected SecondLevel $second,
    protected ThirdLevel $third
  ) {}
}

class SecondLevel
{
  public function __construct(
    protected ThirdLevel $third
  ) {}
}
/* Some class with parameters */
class ThirdLevel {
  public function __construct(
    protected int $id
  ) {}
}

/* Provider for the class that needs parameters, implementing Provider interface */
class ThirdLevelProvider implements \Dein\Interfaces\Provider<ThirdLevel>
{
  /* The only method needed to implement, that will return the instance */
  public function get(\Dein\Reflection\ClassInspector<ThirdLevel> $class):ThirdLevel
  {
    return new ThirdLevel(rand(50, 100));
  }
}

/* Create the container */
$container = \Dein\ContainerService::start();
/* Add custom providers */
$container->addProvider(ThirdLevelProvider::class);
/* Get the instance */
$instance = $container->get(FirstLevel::class);
var_dump($instance);
