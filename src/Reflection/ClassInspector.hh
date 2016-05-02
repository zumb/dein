<?hh //strict
namespace Dein\Reflection;

use Dein\Interfaces\Provider;
use Dein\ContainerService;

class ClassInspector<Tp> extends \ReflectionClass
{
  public function __construct(
    mixed $class,
    protected ContainerService $container
  ) {
    parent::__construct($class);
  }

  public function instance():Tp
  {
    $constructor = $this->getConstructor();
    $provider = $this->container->getProvider($this);
    if($provider != null) {
      // UNSAFE
      return $provider->get($this);
    } elseif($constructor != null) {
      return $this->newInstanceArgs(
        $this->container->resolve($constructor)
      );
    } else {
      return $this->newInstance();
    }
  }
}
