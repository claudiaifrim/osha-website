<table border="0" cellpadding="28" cellspacing="0" width="800">
  <tbody>
  <tr>
    <td style="padding-top: 15px; padding-bottom: 15px; font-family: Arial,sans-serif; font-size: 12px; color: #333333;">
      <?php print $body_content; ?>
      <?php if ($bundle == 'press_release') {
              print('<h2>');print t('Press contacts');print('</h2>');
              print $contacts;
            } ?>
    </td>
  </tr>
  </tbody>
</table>