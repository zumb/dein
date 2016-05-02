<?hh //strict
namespace Dein;

use Dein\Reflection\ClassInspector;
use Dein\Interfaces\Provider;
use Dein\Providers\ProvidersProvider;
use Dein\Providers\ContainerServiceProvider;

class ContainerService
{
  protected  Map<classname<mixed>, mixed> $providers = Map{};

  public function __construct() {
    echo "container";
    $this->addProvider(new ContainerServiceProvider($this));
    $this->addProvider(ProvidersProvider::class);
  }

  public function get(string $class):mixed
  {
    $reflection = new ClassInspector($class, $this);
    return $reflection->instance();
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
    $provide = new \ReflectionMethod($provider, "get");
    $this->providers->set($provide->getReturnTypeText(), $provider);
    return $this;
  }

  public function getProvider(\ReflectionClass $class):?Provider<mixed>
  {
    foreach($this->providers as $returns => $provider) {
      if($class->isSubclassOf($returns) || $class->getName() == $returns) {
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
}
