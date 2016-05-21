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

class Randomizer {
  public function random() {
    return rand(50, 100);
  }
}

/* Provider for the class that needs parameters, implementing Provider interface */
class ThirdLevelProvider implements \Zumb\Dein\Interfaces\Provider<ThirdLevel>
{
  /* The only method needed to implement, that will return the instance */
  <<Inject('Example\Randomizer')>>
  public function get(\Zumb\Dein\Reflection\ClassInspector<ThirdLevel> $class, ... $dependencies):ThirdLevel
  {
    $randomizer = array_pop($dependencies);
    return new ThirdLevel($randomizer->random());
  }
}

/* Create the container */
$container = \Zumb\Dein\Factory::create();
/* Add custom providers */
$container->providers->add(new ThirdLevelProvider());
/* Get the instance */
$instance = $container->get(FirstLevel::class);
var_dump($instance);
