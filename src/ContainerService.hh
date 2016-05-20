<?hh //strict
namespace Dein;

use Dein\Reflection\ClassInspector;
use Dein\Interfaces\Provider;
use Dein\Providers\ProvidersProvider;
use Dein\Providers\ContainerServiceProvider;

class ContainerService
{
  protected  Map<classname<mixed>, mixed> $providers = Map{};

  public function __construct(
    protected Instantiator $instantiator
  ) {}

  public function get(string $class):mixed
  {
    return $this->instantiator->make(
      $this->instantiator->inspector($class), $this
    );
  }

  public function resolve(\ReflectionMethod $method):Map<string, mixed>
  {
    $resolvedParameters = new Map(null);
    foreach ($method->getParameters() as $parameter) {
      $resolvedParameters->set(
        $parameter->getName(), $this->get($parameter->getTypeText())
      );
    }
    return $resolvedParameters;
  }

  public function addProvider(mixed $provider):this
  {
    $provide = $this->instantiator->method($provider, "get");
    $this->providers->set($provide->getReturnTypeText(), $provider);
    return $this;
  }

  public function getProvider(ClassInspector<mixed> $class):?Provider<mixed>
  {
    foreach($this->providers as $returns => $provider) {
      if($class->is($returns)) {
        if($provider instanceof Provider) {
          return $provider;
        } elseif(is_string($provider)) {
          $providerInstance = $this->get($provider);
          invariant($providerInstance instanceof Provider, "Not a provider");
          return $providerInstance;
        }
      }
    }
    return null;
  }

  public static function start():ContainerService
  {
    $container = new self(new Instantiator());
    $container->addProvider(new ContainerServiceProvider($container));
    $container->addProvider(ProvidersProvider::class);
    return $container;
  }
}
