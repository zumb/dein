<?hh //strict
namespace Zumb\Dein;

class Resolver
{
  public function parameters(\ReflectionMethod $method, ContainerService $container):array<mixed>
  {
    $parameters = [];
    foreach ($method->getParameters() as $parameter) {
      $parameters[] = $container->get($parameter->getTypeText());
    }
    return $parameters;
  }

  public function attributes(\ReflectionMethod $method, ContainerService $container):array<mixed>
  {
    $parameters = [];
    $dependencies = $method->getAttribute('Inject');
    if($dependencies) {
      foreach ($dependencies as $dependency) {
        invariant(is_string($dependency), "Dependency should be a class");
        $parameters[] = $container->get($dependency);
      }
    }
    return $parameters;
  }
}
