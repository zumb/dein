<?hh //strict
namespace Zumb\Dein;

use Zumb\Dein\Reflection\ClassInspector;

class ContainerService
{
  public function __construct(
    protected Instantiator $instantiator,
    protected Resolver $resolver,
    public ProvidersPool $providers
  ) {}

  public function get(string $class):mixed
  {
    $inspector = $this->instantiator->inspector($class);
    $provider = $this->providers->get($inspector);
    if($provider != null) {
      $method = $this->instantiator->method($provider, "get");
      return $method->invokeArgs($provider,
        array_merge([$inspector], $this->resolver->attributes($method, $this))
      );
    }
    return $this->create($inspector);
  }

  public function call(\ReflectionMethod $method, mixed $object):mixed
  {
    return $method->invokeArgs($object,
      array_merge(
        $this->resolver->parameters($method, $this),
        $this->resolver->attributes($method, $this)
      )
    );
  }

  public function create(ClassInspector<mixed> $class):mixed
  {
    $constructor = $class->getConstructor();
    if($constructor != null) {
      if(count($constructor->getParameters())) {
        return $class->newInstanceArgs(
          $this->resolver->parameters($constructor, $this)
        );
      }
    }
    return $class->newInstance();
  }



}
