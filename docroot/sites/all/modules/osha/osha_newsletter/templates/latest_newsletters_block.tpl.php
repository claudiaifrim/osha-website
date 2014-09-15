<div id="latest-newsletters-block">
  <?php
  if (!empty($items)){
    foreach($items as $item){
  ?>
      <h2><?php print l($item['title'], url($item['url'], array('absolute' => TRUE)), array(
          'attributes' => array('style' => 'color: #003399; text-decoration: none;'),
          'external' => TRUE
        )); ?></h2>
  <?php
      foreach($item['items'] as $element){
        print(render($element));
      }
    }
  } else {
    print t('No newsletters available.');
  }
  ?>
</div>